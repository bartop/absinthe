
from conans import ConanFile

class Absinthe(ConanFile):
    name = "absinthe"
    version = "0.1.0"
    exports_sources = "include/*"
    no_copy_source = True

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
