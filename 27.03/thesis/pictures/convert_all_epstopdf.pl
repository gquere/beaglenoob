#!/usr/bin/perl
use File::Basename;
opendir(DOT,".") ||
    die "Cannot opendir . (serious dainbramage): $!";
	foreach (sort readdir(DOT)) {
	$help = basename ($_,'.eps');
	if (-e "$help.eps")
		{
         	 print "converting ", $help , "\n";
		 system("epstopdf $help.eps");
		}
    }
closedir(DOT);
