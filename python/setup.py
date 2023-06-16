from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "0.0.1"

ext_modules = [
        Pybind11Extension(
            "Quat",
            ["./bind11.cpp"],
            define_macros = [ ("VERSION_INFO", __version__), ]
        )
    ]

setup(
    name="Quat",
    version=__version__,
    autor="Qi Zhang",
    description="A python binding for Quaternion",
    ext_modules=ext_modules,
)
