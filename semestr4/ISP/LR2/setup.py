from setuptools import setup

setup(
    name='serializers',
    version='1.0',
    description='LR2',
    packages=['serializers'],
    author='Mikhail Krishtapovich',
    author_email='mkrishtapovich@gmail.com',
    entry_points={
        'console_scripts': [
            'run = serializers.main:main'
        ]})
