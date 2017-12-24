use Perl6;

use Crypt::RC4;

# your message must be encoded to ascii
my @vector = <item1 item2 item3 item4>;
my @temp_vector;

for @vector -> $line {
	$_++;
	my $fraction = $line.encode("ascii");
	say "Message of line $_ in utf-8: " ~ $fraction.decode("utf-8"); 

	#if passphrase is different decryption won't work, as expected
	my $encrypt = RC4( 12, $fraction );

	#if you try to decode the message to ascii or utf-8 it'll fail
	say $encrypt;
	
	#decrypt message
	my $decrypt = RC4( 12, $encrypt );
	say "Decrypted message of line $_ in utf-8: " ~ $decrypt.decode("utf-8") ~ "\n";

	@temp_vector.push($decrypt.decode("utf-8"));
}
@vector = @temp_vector;
say "Final array: " ~ @vector;
