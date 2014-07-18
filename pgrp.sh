#!/bin/bash

sort /boot/vmlinuz-2.6.32-431.11.2.el6.x86_64 | sed '/linux/'p
