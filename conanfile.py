
from conans import ConanFile, CMake

class Absinthe(ConanFile):
    generators = "cmake_find_package"
    requires = "catch2/2.13.6"
    name = "absinthe"
    version = "0.1.0"
    exports_sources = "include/*"
    no_copy_source = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()
        cmake.install()

    def package(self):
        self.copy("*.hpp")
        self.copy("CMakeLists.txt")

    def package_id(self):
        self.info.header_only()
