import os
import re
import shutil
import sys
import platform
import subprocess
from pathlib import Path

from setuptools import setup, find_packages, findall, Extension
from setuptools.command.build_ext import build_ext
from distutils.version import LooseVersion
from distutils import log


class CMakeExtension(Extension):
    def __init__(self, name, lib_dir, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)
        self.name = name
        self.lib_dir = lib_dir


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            cmake_version = LooseVersion(
                re.search(r'version\s*([\d.]+)', out.decode()).group(1))
            if cmake_version < '3.1.0':
                raise RuntimeError("CMake >= 3.1.0 is required on Windows")

        for ext in self.extensions:
            self.build_extension(ext)
            # self.install_extension(ext)

    def finalize_options(self):
        super().finalize_options()

        build_type = 'debug' if self.debug else 'release'

        build_temp = Path(self.build_temp)
        self.build_temp = str(build_temp.with_name("%s.%s" % (build_type, build_temp.name)))
        build_lib = Path(self.build_lib)
        self.build_lib = str(build_lib.with_name("%s.%s" % (build_type, build_lib.name)))

    def build_extension(self, ext):
        extdir = os.path.abspath(
            os.path.dirname(self.get_ext_fullpath(ext.name)))
        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{}={}'.format(
                cfg.upper(),
                extdir)]
            if sys.maxsize > 2 ** 32:
                cmake_args += ['-A', 'x64']
            build_args += ['--', '/m']
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args,
                              cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args,
                              cwd=self.build_temp)
        print()  # Add an empty line for cleaner output

    # def install_extension(self, ext):
    #     extname = os.path.abspath(self.get_ext_fullpath(ext.name))

    #     lib_dir = os.path.join(ext.sourcedir, ext.lib_dir, ext.name) + ".so"
    #     log.info("Copying file %s to '%s'", os.path.basename(extname), lib_dir)
    #     shutil.copy(extname, lib_dir)


def find_modules(dir=os.curdir):
    return [x for x in findall(dir) if os.path.splitext(x)[1] == '.py']


setup(
    name='pyviewer',
    version='0.0.1',
    author='Francisca Gil',
    author_email='franciscagil@nyu.edu',
    description='',
    long_description='',
    scripts=find_modules('bin'),
    package_dir={'': 'py'},
    ext_modules=[CMakeExtension('pyviewer/_pyviewer', 'py')],
    cmdclass=dict(build_ext=CMakeBuild),
    zip_safe=False,
)