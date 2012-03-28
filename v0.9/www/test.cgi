#!/usr/bin/perl
use strict;
main();

sub main ()
{
my $input;
read( STDIN, $input, $ENV{CONTENT_LENGTH} );	# fetch arguments from GET method
my @out = split(/=/, $input);			# split the arguments (1 argument) into a table

if($out[1] =~ "on" )
	{
	my $result = `./led.sh 1`;
	}
else
	{
	my $result = `./led.sh 0`;
	}

print( STDOUT "Content-Type:text/html\r\n" );
print( STDOUT "Status: 200 Ok\r\n" );
print( STDOUT "\r\n" );
print( STDOUT <<HTML );
<html>
	<body>
		<h1> LED control <em>$out[1]</em> </h1>
		<form action="test.cgi" method="POST">
			<input type="submit" name="Button1" value="on">
			<input type="submit" name="Button2" value="off">
		</form>
	</body>
</html>
HTML
}
