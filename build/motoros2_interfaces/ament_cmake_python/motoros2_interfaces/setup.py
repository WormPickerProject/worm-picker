from setuptools import find_packages
from setuptools import setup

setup(
    name='motoros2_interfaces',
    version='0.1.3',
    packages=find_packages(
        include=('motoros2_interfaces', 'motoros2_interfaces.*')),
)
