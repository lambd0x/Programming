#!/usr/bin/perl6
# RadixSort. Time complexities: Best = (n) Average = (n²) Worst = (n²). Space Complexity: Worst = (n²)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub radixSort (@ints) {
    my $maxlen = [max] @ints».chars; my @list = @ints».fmt("\%0{$maxlen}d");
 
    for reverse ^$maxlen -> $r {
        my @buckets = @list.classify( *.substr($r,1) ).sort: *.key; if !$r and @buckets[0].key eq '-' { @buckets[0].value .= reverse }
        @list = flat map *.value.values, @buckets;
    }
    @list».Int;
}

my @array = store; say @array;
say radixSort @array;
