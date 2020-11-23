# Warning! This is an engine system file!
# Any changes could break internal systems!
# Author: Mario
# Project: DreamcastSDK
# Created: 23.11.2020 13:47

import sys


class StdoutHook:
    def __init__(self):
        self.value = ""

    def write(self, txt):
        self.value += txt


stdout_hook = StdoutHook()
sys.stdout = stdout_hook
sys.stderr = stdout_hook
