use v6;
# generates a set of random integer numbers to be used in the other programs as input.

sub gen($higher_limit) { unlink "file$higher_limit"; for 1..$higher_limit { spurt "input$higher_limit", "{Int($higher_limit.rand)} {Int($higher_limit.rand)}\n", :append; } }

sub MAIN{ for 1..3 -> $index { $_ = prompt "Define the upper limit of the random integer number set [0, x) for list $index:\n"; gen($_); } }
