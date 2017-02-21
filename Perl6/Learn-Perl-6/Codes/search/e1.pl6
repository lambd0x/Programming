#!/usr/bin/perl6
#iBinary search using arrays. Time complexities worst: O(log(n)), best: Omega(log(n)). Space complexities: Tetha(1)
sub input() { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub binSearch(@tmp, $key) {
	my $low = 0, my $high = @tmp.end;
	while $low <= $high {
		my $middle = ($low + $high) div 2; 
		{say "Found it"; return 0} if $key == @tmp[$middle]; $high = $middle-1 if $key < @tmp[$middle]; $low = $middle+1 if $key > @tmp[$middle];
	}; say "didn't find it";
}

my @array = input;
binSearch @array, @array.shift;
