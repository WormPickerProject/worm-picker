from setuptools import find_packages
from setuptools import setup

setup(
    name='industrial_msgs',
    version='0.7.3',
    packages=find_packages(
        include=('industrial_msgs', 'industrial_msgs.*')),
)
