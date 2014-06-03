# plain simple Makefile for hdate
#
# Author : Mohammad Hafiz bin Ismail
# date : 19 April 2005
#

CC=gcc
CFLAGS=-O2 -pedantic -ansi -Wall
INSTALL=install
PREFIX=/usr/local


all :
	$(CC) $(CFLAGS) hdate.c -o hdate

install : all
	strip hdate
	$(INSTALL) -m755 hdate $(PREFIX)/bin

clean : 
	rm -f hdate

