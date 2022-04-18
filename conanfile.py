
from conans import ConanFile

class Absinthe(ConanFile):
    generators = "cmake_find_package"
    requires = "catch2/2.13.6"
    name = "absinthe"
    version = "0.1.0"
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.hpp")
        self.copy("CMakeLists.txt")

    def package_id(self):
        self.info.header_only()
