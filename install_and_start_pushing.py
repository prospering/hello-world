"""
Module to create a bagtower device, this requires to have a valid account on
https://bagtower.bag-era.fr/


@organization: BAG ERA
@copyright: 2020
@contact: contact_bagtower@bag-era.fr
"""
import argparse
import os
import shutil
import sys
import urllib.request

VERSION = "1.2.12"

BASE_URL = "https://scripts.bagtower.bag-era.fr"
PUSH_DEVICE_FILE_NAME = "push_device_info.py"
PUSH_DEVICE_FILE_URI = "%s/%s" % (BASE_URL, PUSH_DEVICE_FILE_NAME)

REQUIREMENTS_FILE_URL = "%s/requirements-create.txt" % BASE_URL

HOME_DIR = os.path.expanduser('~')

BAGTOWER_DIR = os.path.join(HOME_DIR, ".bagtower")
BAGTOWER_DIR_PUSH = os.path.join(BAGTOWER_DIR, "push")
LOCAL_PUSH_DEVICE = os.path.join(BAGTOWER_DIR_PUSH, PUSH_DEVICE_FILE_NAME)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="install bagtower push_device script and start monitoring you device")
    parser.add_argument("--device_id", help="device id (can be found in device_config file)", type=str, required=True)
    parser.add_argument("--api_key", help="api Key (can be found in device_config file)", type=str, required=True)
    args = parser.parse_args()
    print(".. creating bagtower dir")

    os.makedirs(BAGTOWER_DIR, exist_ok=True)
    shutil.rmtree(BAGTOWER_DIR_PUSH, ignore_errors=True)
    os.makedirs(BAGTOWER_DIR_PUSH, exist_ok=True)
    os.makedirs(os.path.join(BAGTOWER_DIR_PUSH, "requirements"), exist_ok=True)

    # check pip is installed to be able to install requirements
    try:
        import pip  # pylint: disable=unused-import
    except ImportError:
        print(80 * "!")
        print('pip is missing, cannot install requirements')
        print(80 * "!")
        print()
        print('to install pip on debian like please run:')
        print()
        print('sudo apt install python3-pip')
        print()
        print('or go to:')
        print()
        print('https://pip.pypa.io/en/stable/installing/')
        print()
        sys.exit(1)

    print(".. get push device script %s" % PUSH_DEVICE_FILE_URI)
    urllib.request.urlretrieve(PUSH_DEVICE_FILE_URI, LOCAL_PUSH_DEVICE)
    urllib.request.urlretrieve("%s/%s" % (BASE_URL, "requirements-push-top.txt"),
                               os.path.join(BAGTOWER_DIR_PUSH, "requirements.txt"))
    urllib.request.urlretrieve("%s/requirements/%s" % (BASE_URL, "requirements.txt"),
                               os.path.join(BAGTOWER_DIR_PUSH, "requirements", "requirements.txt"))
    urllib.request.urlretrieve("%s/requirements/%s" % (BASE_URL, "requirements-setup.txt"),
                               os.path.join(BAGTOWER_DIR_PUSH, "requirements", "requirements-setup.txt"))
    urllib.request.urlretrieve("%s/requirements/%s" % (BASE_URL, "requirements-push.txt"),
                               os.path.join(BAGTOWER_DIR_PUSH, "requirements", "requirements-push.txt"))

    print(".. install python requirements")
    pip_install_cmd = "%s -m pip install -r %s" % (sys.executable, os.path.join(BAGTOWER_DIR_PUSH, "requirements.txt"))
    print(pip_install_cmd)
    ret = os.system(pip_install_cmd)
    if ret != 0:
        print(80 * "!")
        print('failed to install requirements')
        print(80 * "!")
        sys.exit(ret)

    print(".. start pushing device info")
    push_cmd = "%s %s --device_id %s --api_key %s" % (sys.executable, LOCAL_PUSH_DEVICE, args.device_id, args.api_key)
    ret = os.system(push_cmd)
    if ret == 0:
        print(80 * "!")
        print("!! all set, you device is now pushing it's information periodically !!")
        print(80 * "!")
    else:
        print(80 * "!")
        print('an unexpected error occurred, check the logs for more information')
        print(80 * "!")
        sys.exit(ret)
