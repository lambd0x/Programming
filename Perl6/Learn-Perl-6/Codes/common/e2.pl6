use Perl6;

sub menu() {
	say q:to/^/;
	Simple Calc
	+	to	addition
	-	to	subtraction
	/	to	division
	*	to 	multiplication
	q	to	quit
	^
	return prompt "";
}

sub addition($result) {
	say q:to/^/;
	Insert the numbers to add them
	Press q to stop adding
	^
	my $value = $result;
	loop {
		$_ = prompt '';
		if "q" eq $_ {	say "Result: $value"; return $value;}
		$value += $_;
	}
}

sub subtraction($result) {
	say q:to/^/;
	Insert the numbers to sub them
	Press q to stop subtracting
	^
	my $value = $result;
	loop {
		$_ = prompt '';
		if "q" eq $_ {	say "Result: $value"; return $value;}
		$value -= $_;
	}
}

sub division($result) {
		say q:to/^/;
	Insert the numbers to divide them
	Press q to stop dividing
	^
	my $value = $result;
	loop {
		$_ = prompt '';
		if "q" eq $_ {	say "Result: $value"; return $value;}
		$value /= $_;
	}
}

sub multiplication($result) {
		say q:to/^/;
	Insert the numbers to multiplicate them
	Press q to stop multiplicating
	^
	my $value = $result;
	loop {
		$_ = prompt '';
		if "q" eq $_ {	say "Result: $value"; return $value;}
		$value *= $_;
	}
}

my $result;
loop {
	given menu() {
		when "q" {	say "Final result: $result"; last;	}
		when "+" { 	$result = addition($result);		}
		when "-" {	$result = subtraction($result);		}
		when "/" { 	$result = division($result);		}
		when "*" {	$result = multiplication($result);	}
		default  { 	say "operation not available";		}
	}
}
