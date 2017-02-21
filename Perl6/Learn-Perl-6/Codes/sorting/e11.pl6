#!/usr/bin/perl6
# BucketSort insertion if elems less than 11 or else uses countingSort. 
# Time complexities: Best = (n+k) Average = (n²) Worst = (n²). Space complexity: Worst = (n+k)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub insertionSort(@tmp) { for 1..^@tmp -> $i { my $j = $i-1; $_ = @tmp[$i]; while $j >= 0 and @tmp[$j] > $_ { @tmp[$j+1,$j] = @tmp[$j,$j+1]; $j--; } } }

sub countingSort(@tmp) { my $off = @tmp.min; (my @counts)[$_ - $off]++ for @tmp; return flat @counts.kv.map: { ($^k + $off) xx ($^v // 0) } }

sub bucketSort(@tmp) {
	my $lim = ceiling((@tmp.max+1)/10); my (@tmp2, @tmp3); 
	{ my $el = +@tmp[$_] div $lim; @tmp2[$el].push(@tmp[$_]) if @tmp2; @tmp2[$el].push(@tmp[$_]) unless @tmp2; } for ^@tmp;
	{ insertionSort @tmp2[$_] if 1 < @tmp2[$_].elems < 11; @tmp2[$_] = countingSort @tmp2[$_] if 11 < @tmp2[$_].elems; @tmp3.splice($_,0, @tmp2[$_])} for ^@tmp2; say @tmp3;
}

my @array = store; say @array;
bucketSort @array;
