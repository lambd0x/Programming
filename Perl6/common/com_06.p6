use Perl6;

my $start = now;
for 1..100 -> $a { say $a ~ " is prime!" if $a.is-prime;}
say now - $start ~ " seconds";
