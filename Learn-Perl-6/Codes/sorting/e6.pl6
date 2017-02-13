#!/usr/bin/perl6
# HeapSort. Time complexities: Average = (nlog(n)). Space complexities: Worst = (1)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub heapSort(@tmp) { shiftDown $_, @tmp.end, @tmp for (0..^@tmp/2).reverse; { @tmp[0,$_] .= reverse; shiftDown 0, $_-1, @tmp} for (1..^@tmp).reverse; }
 
sub shiftDown($start, $end, @tmp) { my $root = $start;
    while (my $child = $root * 2 + 1) <= $end { $child++ if $child + 1 <= $end and [<] @tmp[$child,$child+1]; return if @tmp[$root] >= @tmp[$child];
        @tmp[$root, $child] .= reverse; $root = $child;
    }
}

my @array = store; say @array;
heapSort @array; say @array;
