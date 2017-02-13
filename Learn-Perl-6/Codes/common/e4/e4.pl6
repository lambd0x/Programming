#!/usr/bin/perl6

sub menu() {
	say q:to/^/;
	1 to insert an entry
	2 to remove an entry
	3 to search for an entry
	4 to update an entry
	q to exit application
	^
	return prompt "";
}

sub menuSearch() {
	say q:to/^/;
	1 to search for a specific entry
	2 to display everything
	q to get back to main menu
	^
	return prompt "";
}

sub insert(@lines) {
	my @receives = @lines;
	@receives.push(prompt "Insert your name and age, please: ");
	return @receives;
}

sub remove(@lines) {
	my @removes = @lines;
	say "It's empty." unless @removes; { my $target = prompt "Delete: "; 
	say @removes[@removes.grep($target, :k)]:delete ~ " was removed"; } if @removes; 
	return @removes;
}

sub search(@lines) {
	say "It's empty." unless @lines; 
	{ loop { given menuSearch() {
			when "1" { my $target = prompt "Search for: "; 
				   say $target eq any(@lines) ?? "$target exists." !! "$target doesn't exist."; }
			when "q" { last; } 
			default  { say "contents"; for @lines -> $line-item { say $line-item; } }	
		}
	} } if @lines;	
}

sub update(@lines) {
	my @entries = @lines;
	say "It's empty." unless @entries;
	{ my $target = prompt "Search and replace: "; my $update = prompt "Update it to: "; 
	say @entries.splice(@entries.grep($target, :k) -1, 1, $update) ~ " updated to $update"; } if @entries;
	return @entries;
}

sub MAIN{
	my @lines;
	say "Nothing loaded" unless "e4.conf".IO.e;
	{ say "Data loaded"; for "e4.conf".IO.lines -> $lines { @lines.push($lines); } } if "e4.conf".IO.e;
	loop {
		given menu() {
			when "1" { @lines = insert(@lines);  }
			when "2" { @lines = remove(@lines);  }
			when "3" { search(@lines);           } 
			when "4" { @lines = update(@lines);  }
			when "q" { say "Option 7"; last;     }
			default  { say "Option unavailable"; }
		}
	}
	unlink "e4.conf"; for @lines -> $lines { spurt "e4.conf", "$lines\n", :append; }
}
