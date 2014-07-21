
%define name    tcpdump
%define version 4.6.1
%define release 1

Summary: A tool for dumping traffic on a network
Name: %{name}
Version: %{version}
Release: %{release}
License: BSD license
Group: Applications/System
Source: http://www.tcpdump.org/release/tcpdump-%{version}.tar.gz
URL: http://www.tcpdump.org/
BuildRoot: /var/tmp/%{name}-%{version}

%description
Tcpdump prints out a description of the contents of packets on a network interface that match the boolean expression. It can also be run with the -w flag, which causes it to save the packet data to a file for later analysis, and/or with the -r flag, which causes it to read from a saved packet file rather than to read packets from a network interface. It can also be run with the -V flag, which causes it to read a list of saved packet files. In all cases, only packets that match expression will be processed by tcpdump.

%package devel
Summary: Libraries, includes, etc to develop tcpdump applications
Group: Libraries

%description devel
Libraries, include files, etc you can use to develop tcpdump applications.

%prep
%setup

%build
%configure
make

%install
if [ -d $RPM_BUILD_ROOT ]; then rm -rf $RPM_BUILD_ROOT; fi
mkdir -p $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install
#%clean
#if [ -d $RPM_BUILD_ROOT ]; then rm -rf $RPM_BUILD_ROOT; fi

%files
%defattr(-,root,root)
#%doc AUTHORS COPYING ChangeLog INSTALL NEWS README TODO doc
#%{_libdir}/libsndfile.so.*
#%{_bindir}/*
%{_sbindir}/*
%{_mandir}/man1/*
#%{_datadir}/octave/site/m/*
#%{_defaultdocdir}/libsndfile1-dev/html/*

%files devel
#%defattr(-,root,root)
#%{_libdir}/libsndfile.a
#%{_libdir}/libsndfile.la
#%{_libdir}/libsndfile.so
#%{_includedir}/sndfile.h
#%{_libdir}/pkgconfig/sndfile.pc

%changelog
* Mon Jul 21 2014 Son Nguyen <ngocson2vn@gmail.com>
- Created tcpdump.spec

