use Perl6;
# BucketSort sorting with insertionSort. Time complexities: Best = (n+k), Average = (n²) Worst = (n²). Space complexity: Worst = (n+k)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub insertionSort(@tmp) { for 1..^@tmp -> $i { my $j = $i-1; $_ = @tmp[$i]; while $j >= 0 and @tmp[$j] > $_ { @tmp[$j+1,$j] = @tmp[$j,$j+1]; $j--; } } }

sub bucketSort(@tmp) {
	my $lim = ceiling((@tmp.max+1)/10); my (@tmp2, @tmp3);
	{ my $el = +@tmp[$_] div $lim; @tmp2[$el].push(@tmp[$_]) if @tmp2; @tmp2[$el].push(@tmp[$_]) unless @tmp2; } for ^@tmp;
	{ insertionSort @tmp2[$_] if 1 < @tmp2[$_].elems < 11; @tmp3.splice($_,0, @tmp2[$_]) } for ^@tmp2; say @tmp3;
}

my @array = store; say @array;
say bucketSort @array;
