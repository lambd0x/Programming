use Perl6;
# Selection sort, Time complexities: Average = (n²). Space complexities: Worst = (1)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

sub selectionSort(@tmp) { for ^@tmp -> $min { @tmp[$min,$_] = @tmp[$_,$min] if @tmp[$min] > @tmp[$_] for $min^..^@tmp; }; say @tmp; }

my @array = store; @array.say;
selectionSort @array;
