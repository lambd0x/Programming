#!/usr/bin/perl6

#bidimensional array 
my @arrayOne[3;3];
for 0..2 X 0..2 -> ($a, $b) {
		my $input = prompt "Input or q: ";
		last if "q" eq $input;
		@arrayOne[$a;$b] = $input;
}

for @arrayOne -> $one, $two, $three {
	say $one ~ " " ~ $two ~ " " ~ $three;
}

#tridimensional array
my @arrayTwo[2;2;2];
for 0..1 X 0..1 X 0..1 -> ($a,$b,$c) {
			my $input = prompt "Input or q: ";
			last if "q" eq $input;
			@arrayTwo[$a;$b;$c] = $input;
}

say @arrayTwo;

#pour in a fixed size array
my @arrayThree[3;3;3] Z= 0..26;
say @arrayThree;
