#!/usr/bin/perl6
# MergeSort. Time completixies: Average = nlog(n)). Space complexities: Worst = (n)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub mergeSort(@tmp) {
    return @tmp if @tmp <= 1;
 
    my $m = @tmp.elems div 2; my @l = flat mergeSort @tmp[^$m]; my @r = flat mergeSort @tmp[$m..^@tmp];
    return @l, @r if @l[*-1] before @r[0]; return flat gather { take @l[0] before @r[0] ?? @l.shift !! @r.shift while @l and @r; take @l, @r; }
}

my @array = store; say @array;
@array = mergeSort @array; say @array;
