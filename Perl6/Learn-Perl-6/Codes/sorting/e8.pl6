use Perl6;
# CountingSort. Time complexities: Best = (n) Average = (n+k) Worst = (n+k). Space complexities: Worst = (k)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub countingSort(@tmp) { my $off = @tmp.min; (my @counts)[$_ - $off]++ for @tmp; flat @counts.kv.map: { ($^k + $off) xx ($^v // 0) } }

my @array = store; say @array;
say countingSort @array;
