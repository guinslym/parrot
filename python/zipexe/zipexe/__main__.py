#!/usr/bin/env python

import sys

if __package__ is None and not hasattr(sys, "frozen"):
    # direct call of __main__.py
    import os.path
    path = os.path.realpath(os.path.abspath(__file__))
    sys.path.append(os.path.dirname(os.path.dirname(path)))

import zipexe
import zipexe.echo

if __name__ == '__main__':
    print 'get it'
    zipexe.run()
    zipexe.echo.run()

