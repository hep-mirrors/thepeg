#!/usr/bin/perl
#
# Reformat ThePEG headerfiles using the old classdoc documentation to
# instead use the new Doxygen format. Note that the header files need
# to be gone through by hand afterwards to fix details.
#

$savedcomment = "";
$saveddecl = "";

$inclass = 0;

sub dumpit {
  if ( $savedcomment ) {
    $savedcomment =~ /^(\s*)\/\//;
    $leading = $1;
    $savedcomment =~ s/(\s*)\/\//$1 */g;
    $savedcomment =~ s/<!id>/<code>/g;
    $savedcomment =~ s/<!!id>/<\/code>/g;
    $savedcomment =~ s/<!+class>//g;
    $savedcomment =~ s/\<a\s+href="http:(\w+)\.html.*\/a\>/\@see $1/g;
#    print "$leading/**\n$savedcomment$leading */\n";
    @decls = split(/(?<=;)\n/, $saveddecl);

    if ( !@decls ) {
      print "$leading/**\n$savedcomment$leading */\n";
    } else {
      foreach ( @decls ) {
	print "$leading/**\n$savedcomment$leading */\n";
	print "$_\n";
      }
    }

  }
  else {
    print $saveddecl if ( $saveddecl );
  }

  $savedcomment = "";
  $saveddecl = "";
}

while ( $line = <> ) {

  if ( $line =~ /^\s*\/\// ) {
    if ( $line =~ /-\*-.*-\*-/ ) {
      print $line;
    }
    elsif ( $line =~ /#include/ ) {
      print $line;
    }
    elsif ( $line =~ /This is the declaration of the/ ) {
      $line  =~ s/<!+(id|class)>//g; 
      $savedcomment = "";
      print $line;
    }
    elsif ( $line =~ / CLASSDOC / ) {
    }
    else {
      if ( $line =~ /\s*\/\/\s*$/ && !$savedcomment ) {}
      else {
	$savedcomment .= $line;
      }
    }
  }
  elsif ( $line =~ /^\s*(class|struct)/ ) {
    $inclass++;
    dumpit();
    print $line;
  }
  elsif ( $line =~ /^\s*};/ ) {
    $inclass--;
    dumpit();
    print $line;
  }
  elsif ( $line =~ /^\s*$/ ) {
    dumpit() if ( $inclass );
    print $line;
  }
  else {
    if ( $inclass ) {
      $saveddecl .= $line;
    } else {
      print $line;
    }
  }
}

dumpit();





