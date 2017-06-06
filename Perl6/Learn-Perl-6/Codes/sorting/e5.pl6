use Perl6;
# QuickSort impl. random pivot, Time complexities: Best = (nlog(n)) Average = (n²) Worst = (n²). Time complexities: Worst = (n)

sub store { my $name = @*ARGS.shift; "$name.txt".IO.words; }

multi quickSort([]) { () }
multi quickSort([$pivot, *@tmp]) { my $before := @tmp.grep(*  before $pivot); my $after  := @tmp.grep(* !before $pivot); flat quickSort($before), $pivot, quickSort($after); }

my @array = store; say @array;
@array = quickSort @array.pick: *; say @array;
