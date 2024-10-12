from setuptools import find_packages
from setuptools import setup

setup(
    name='worm_picker_custom_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('worm_picker_custom_msgs', 'worm_picker_custom_msgs.*')),
)
