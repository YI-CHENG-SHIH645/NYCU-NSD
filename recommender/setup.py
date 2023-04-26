from glob import glob
from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension

print(list(set(glob("src/*.cpp")) - set(glob("src/main.cpp"))))
ext_modules = [
    Pybind11Extension(
        "recommender",
        sorted(list(set(glob("src/*.cpp")) - set(glob("src/main.cpp")))),  # Sort source files for reproducibility
        cxx_std=17,
        include_dirs=["/opt/homebrew/include/eigen3",
                      "/opt/homebrew/include/boost"]
    ),
]

setup(
    name="recommender",
    version='0.0.1',
    author="Yi-cheng",
    author_email="z2x98653322@gmail.com",
    description="Collaborative Filtering Recommender",
    long_description="",
    ext_modules=ext_modules
)
