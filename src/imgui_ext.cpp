#include <imgui_ext.h>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

static inline bool ImCharIsBlankA(char c) { return c == ' ' || c == '\t'; }

static void DataTypeApplyOp(int op, void* output, void* arg1, const void* arg2)
{
    if (op == '+')
        *(double*)output = *(const double*)arg1 + *(const double*)arg2;
    else if (op == '-')
        *(double*)output = *(const double*)arg1 - *(const double*)arg2;
    return;
}

static bool DataTypeApplyOpFromText(const char* buf, const char* initial_value_buf, void* data_ptr, const char* format)
{
    while (ImCharIsBlankA(*buf))
        buf++;

    // We don't support '-' op because it would conflict with inputing negative value.
    // Instead you can use +-100 to subtract from an existing value
    char op = buf[0];
    if (op == '+' || op == '*' || op == '/') {
        buf++;
        while (ImCharIsBlankA(*buf))
            buf++;
    } else {
        op = 0;
    }
    if (!buf[0])
        return false;

    // Copy the value in an opaque buffer so we can compare at the end of the function if it changed at all.
    // IM_ASSERT(data_type < ImGuiDataType_COUNT);
    int data_backup[2];
    // IM_ASSERT(GDataTypeInfo[data_type].Size <= sizeof(data_backup));
    memcpy(data_backup, data_ptr, sizeof(double));

    if (format == NULL)
        format = "%lf";

    int arg1i = 0;
    format = "%lf"; // scanf differentiate float/double unlike printf which forces everything to double because of ellipsis
    double* v = (double*)data_ptr;
    double arg0f = *v, arg1f = 0.0;
    if (op && sscanf(initial_value_buf, format, &arg0f) < 1)
        return false;
    if (sscanf(buf, format, &arg1f) < 1)
        return false;
    if (op == '+') {
        *v = arg0f + arg1f;
    } // Add (use "+-" to subtract)
    else if (op == '*') {
        *v = arg0f * arg1f;
    } // Multiply
    else if (op == '/') {
        if (arg1f != 0.0f)
            *v = arg0f / arg1f;
    } // Divide
    else {
        *v = arg1f;
    } // Assign constant

    return memcmp(data_backup, data_ptr, sizeof(double)) != 0;
}

bool ImGui::InputDouble(const char* label, double* v, double step, double step_fast, const char* format, ImGuiInputTextFlags extra_flags)
{
    // extra_flags |= ImGuiInputTextFlags_CharsScientific;
    return InputScalar(label, (void*)v, (void*)(step > 0.0 ? &step : NULL), (void*)(step_fast > 0.0 ? &step_fast : NULL), format, extra_flags);
}

bool ImGui::InputScalar(const char* label, void* data_ptr, const void* step, const void* step_fast, const char* format, ImGuiInputTextFlags extra_flags)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;

    if (format == NULL)
        format = "%f";

    char buf[64];
    ImFormatString(buf, IM_ARRAYSIZE(buf), format, *(const double*)data_ptr);

    bool value_changed = false;
    if ((extra_flags & (ImGuiInputTextFlags_CharsHexadecimal)) == 0)
        extra_flags |= ImGuiInputTextFlags_CharsDecimal;
    extra_flags |= ImGuiInputTextFlags_AutoSelectAll;

    if (step != NULL) {
        const float button_size = GetFrameHeight();

        BeginGroup(); // The only purpose of the group here is to allow the caller to query item data e.g. IsItemActive()
        PushID(label);
        PushItemWidth(ImMax(1.0f, CalcItemWidth() - (button_size + style.ItemInnerSpacing.x) * 2));
        if (InputText("", buf, IM_ARRAYSIZE(buf), extra_flags)) // PushId(label) + "" gives us the expected ID from outside point of view
            value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialText.Data, data_ptr, format);
        PopItemWidth();

        // Step buttons
        SameLine(0, style.ItemInnerSpacing.x);
        if (ButtonEx("-", ImVec2(button_size, button_size), ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups)) {
            DataTypeApplyOp('-', data_ptr, data_ptr, g.IO.KeyCtrl && step_fast ? step_fast : step);
            value_changed = true;
        }
        SameLine(0, style.ItemInnerSpacing.x);
        if (ButtonEx("+", ImVec2(button_size, button_size), ImGuiButtonFlags_Repeat | ImGuiButtonFlags_DontClosePopups)) {
            DataTypeApplyOp('+', data_ptr, data_ptr, g.IO.KeyCtrl && step_fast ? step_fast : step);
            value_changed = true;
        }
        SameLine(0, style.ItemInnerSpacing.x);
        TextUnformatted(label, FindRenderedTextEnd(label));

        PopID();
        EndGroup();
    } else {
        if (InputText(label, buf, IM_ARRAYSIZE(buf), extra_flags))
            value_changed = DataTypeApplyOpFromText(buf, g.InputTextState.InitialText.Data, data_ptr, format);
    }

    return value_changed;
}