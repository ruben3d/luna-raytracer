#    Copyright (C) 2006-2007 Ruben Moreno Montoliu <ruben3d@gmail.com>
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

################################################################################
#                                                                              #
# release.profile                                                              #
#                                                                              #
# Profile for release version.                                                 #
#                                                                              #
################################################################################

# Prefix used for directory structure
PROFILE_PREFIX=release

# Flags passed to the compiler
PROFILE_CCFLAGS=-Wall -ansi -pedantic-errors -Wextra -O3 -DPROFILE_RELEASE
PROFILE_CXXFLAGS=-Wall -ansi -pedantic-errors -Wextra -O3 -DPROFILE_RELEASE

# Flags passed to the linker
PROFILE_LDFLAGS=

# Flags passed to the archiver
PROFILE_ARFLAGS=

# Flags passed to strip
PROFILE_STRIPFLAGS=
