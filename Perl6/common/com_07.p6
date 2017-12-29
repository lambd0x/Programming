use v6;

#ways of declaring a hash variable
my %hash0 = a => 1, b => 2, c => 3; 	# 1st
my $hash1 = { a => 1, b => 2, c => 3} 	# 2nd

#ways of accessing a hash value
say %hash0{"a"};	#1st

#ways of acessing one or more hash values
say $hash1<a b c>;	#1st

#ways of acessing all the hash values
say %hash0.perl;	#1st

#ways to iterate over a hash variable
for %hash0.keys -> $key { say "$key %hash0{$key}"; }	#1st
for $hash1.kv -> $key, $value { say "$key $value"; }	#2nd

#ways to add a new key
%hash0{"d"} = 4;	#1st
my $e = "e"; $hash1{$e} = 5;	#2nd

#ways to add more values to the same hash key
$hash1.push(<a> => 2, <a> => 3);	#1st
say $hash1<a>;
