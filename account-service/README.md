# account-service
This repository houses the account service designed to manage the personal data of users

## Prerequires
On linux :
```
sudo apt-get install -y gcc
sudo apt-get install -y build-essential
sudo apt-get install -y ninja-build
sudo apt-get install -y cmake
sudo apt-get install -y git
sudo apt-get install -y tar
sudo apt-get install -y zip
sudo apt-get install -y unzip
sudo apt-get install -y curl
sudo apt-get install -y pkg-config
sudo apt-get install -y autoconf
```
On Windows(using powershell as admin):
```
winget install git
winget install cmake
# or
choco install git
choco install cmake
```
## Getting started
To begin, clone the package manager Vcpkg and this repository at the same folder level.
```
cd existing_repo
git clone git@gitlab.com:bcstakecorp/vcpkg.git
git clone git@gitlab.com:bcstakecorp/account-service.git -b your_branch
cd auth-service
```
Configure the project:
```
cmake -S . -B build
```

Build targets:
```
cmake --build build
```

