#!/usr/bin/env perl
my %summary;
while (<>) {
/(.*.(c|h)(pp|c)*):(\d+)(:\d+)?:\serror.*/ and push @{ $summary{$1} }, $4;
print;
}
print "Summary of Errors\n";
foreach $sourcefile ( keys %summary ) {
    print "$sourcefile: @{ $summary{$sourcefile} }\n";
}
