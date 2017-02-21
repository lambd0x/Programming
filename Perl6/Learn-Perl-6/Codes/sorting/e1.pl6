#!/usr/bin/perl6
# bubble sorting algorithm, Time complexities: Average = (n²). Space complexities: Worst: (1)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub bubbleSort(@tmp) { for ^@tmp -> $i { for $i+1..^ @tmp -> $j { @tmp[$j] < @tmp[$i] and @tmp[$i,$j] = @tmp[$j,$i]; } }; say @tmp; }

my @array = store; @array.say;
bubbleSort @array;
