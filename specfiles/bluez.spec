
%define name    bluez
%define version 5.27
%define release 1

Summary: Official Linux Bluetooth protocol stack
Name: %{name}
Version: %{version}
Release: %{release}
License: BSD license
Group: System Environment/Kernel
Source: http://www.kernel.org/pub/linux/bluetooth/bluez-%{version}.tar.gz
URL: http://www.kernel.org/
BuildRoot: /var/tmp/%{name}-%{version}

%description
The kernel modules of BlueZ are included in the Linux 2.6 kernel series. It is always a good idea to use the latest stable kernel. Kernel modules are in the Linux kernel since 2.4.6 release.

%package devel
Summary: Libraries, includes, etc to develop bluez applications
Group: Kernel

%description devel
Libraries, include files, etc you can use to develop bluez applications.

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
%{_sysconfdir}/*
%{_bindir}/*
%{_libdir}/*
%{_prefix}/lib/*
#%{_prefix}/lib64/*
%{_libexecdir}
%{_prefix}/share/*
#%{_mandir}/man1/*
#%{_datadir}/octave/site/m/*
#%{_defaultdocdir}/libsndfile1-dev/html/*
#%{_sbindir}/*

%files devel
#%defattr(-,root,root)
#%{_libdir}/libsndfile.a
#%{_libdir}/libsndfile.la
#%{_libdir}/libsndfile.so
#%{_includedir}/sndfile.h
#%{_libdir}/pkgconfig/sndfile.pc

%changelog
* Wed Dec 30 2014 Son Nguyen <ngocson2vn@gmail.com>
- Created bluez.spec

