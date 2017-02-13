#!/usr/bin/perl6
# Insert sort, Time complexities: Best = (n) Average = (n²) Worst = (n²). Space complexities: Worst = (1)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub insertionSort(@tmp) { for 1..^@tmp -> $i { my $j = $i-1; $_ = @tmp[$i]; while $j >= 0 and @tmp[$j] > $_ { @tmp[$j+1,$j] = @tmp[$j,$j+1]; $j--; } }; say @tmp; }

my @array = store; @array.say;
insertionSort @array;
