#!/usr/bin/python

import subprocess
import os
import signal
from time import sleep

subprocess.call("gcc my_fork.c", shell=True)

with open("output", "w") as outfile:
    proc = subprocess.Popen(["./a.out", "2"], stdout=subprocess.PIPE)
    out, err = proc.communicate()
    outfile.write(out)

with open("output") as f:
    answer = f.readlines()
    if len(answer) < 1:
        print "Your output is blank..."
    elif len(answer) > 1:
        print "Your output should only have one line!"

    # split string into chars, sort, reassemble to check
    answer = "".join(sorted(list(answer[0].strip())))
    if answer == "AABBCCDD":
        print "Your output should parse okay!"
    else:
        print "There was a problem parsing your output. We expected AABBCCDD (not necessarilly in order) and got", answer
