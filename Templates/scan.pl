#!/usr/bin/perl

$class = $ARGV[0];
$fn = $ARGV[1];

if ( $fn eq "ctors" ) {
    @dctor = ( "inline $class\:\:$class()" );
    @cctor = ( "inline $class\:\:$class(const $class & x)" );
    open(IN,"<$class.h") or die "Cannot open '$class.h: $!";
    while ( $line = <IN> ) {
	if ( $line =~ /typedef\s*\b([a-zA-Z][a-zA-Z0-9_]*)\b\s*NthBase/ ) {
	    push @cctor, "$1(x)";
	}
    }
    close(IN);
}

open(IN,"<$class.h") or die "Cannot open '$class.h: $!";

while ( $line = <IN> ) {
    if ( $line =~ /\/\/\#attribute/ ) {
	($variable,$attributes) = split(';',$line);
	($type, $name)=split(' ',$variable);
	@toks=split(' ',$attributes);
	$fname = "";
	$def = "";
	$unit = "";
	$copy = "";
	$pers = "";
	for ( $i=1; $i<@toks; $i++ ) {
	    if ( $toks[$i] =~ /inline=/ ) {
		($dummy, $fname)=split('=',$toks[$i]);
	    }
	    elsif ( $toks[$i] =~ /D=/ ) {
		($dummy, $def)=split('=',$toks[$i]);
	    }
	    elsif ( $toks[$i] =~ /U=/ ) {
		($dummy, $unit)=split('=',$toks[$i]);
	    }
	    elsif ( $toks[$i] eq "copy" ) {
		$copy = $toks[$i];
	    }
	    elsif ( $toks[$i] eq "persistent" ) {
		$pers = $toks[$i];
	    }
	}
	if ( $unit ) {
	    $def = "$def*$unit";
	}
	if ( $fn eq "inlinedecl" && $fname ) {
	    print "  inline $type $fname() const;\n\n";
	}
	elsif ( $fn eq "inlineimpl" ) {
	    print "inline $type $ARGV[0]::$fname() const {\n  return $name;\n}\n\n";
	}
	if ( @dctor && $def ne "" ) {
	    push @dctor, "$name($def)";
	}
	if ( @cctor && $copy ) {
	    push @cctor, "$name(x.$name)";
	}
	if ( $fn eq "persistfn" && $pers ) {
	    push @persist, "$name";
	}
    }
}

if ( @dctor > 0 ) {
    print $dctor[0];
    if ( @dctor > 1 ) {
	print "\n  : $dctor[1]";
	for ( $i = 2; $i < @dctor; $i++ ) {
	    print ", $dctor[$i]";
	}
    }
    print " {}\n\n";
}
if ( @cctor > 0 ) {
    print $cctor[0];
    if ( @cctor > 1 ) {
	print "\n  : $cctor[1]";
	for ( $i = 2; $i < @cctor; $i++ ) {
	    print ", $cctor[$i]";
	}
    }
    print " {}\n\n";
}
if ( $fn eq "persistfn" ) {
    print "void $class\:\:persistentOutput(PersistentOStream & os) const {\n";
    if ( @persist > 0 ) {
	print "  os << $persist[0]";
    }
    for ( $i=1; $i < @persist; $i++ ) {
	print " << $persist[$i]";
    }
    if ( @persist > 0 ) {
	print ";\n";
    }
    print "}\n\nvoid $class\:\:persistentInput(PersistentIStream & is) const {\n";
    if ( @persist > 0 ) {
	print "  is >> $persist[0]";
    }
    for ( $i=1; $i < @persist; $i++ ) {
	print " >> $persist[$i]";
    }
    if ( @persist > 0 ) {
	print ";\n";
    }
    print "}\n\n";
}

