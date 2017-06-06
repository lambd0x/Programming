use Perl6;

use Crypt::RC4;

# your message must be encoded to ascii
my $plaintext = "Source code is bullshit!\n".encode("ascii");
say "Initial message in utf-8: " ~ $plaintext.decode("utf-8"); 

#if passphrase is different decryption won't work as expected
my $encrypt = RC4( 12, $plaintext );

#if you try to decode the message to ascii or utf-8 it'll fail
say $encrypt;

my $decrypt = RC4( 12, $encrypt );
say "Decrypted message in utf-8: " ~ $decrypt.decode("utf-8");

#---------------------------------- 
