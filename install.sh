#!/bin/sh
# ############################################################################
# EXECUTABLE: install.sh		  			                                 #
# PACKAGE: libtools version 0.1.0	                                         #
# ############################################################################
set -eu
OPTARG=
OPTIND=0
cat <<-'EOF'
	Usage: sudo ./install.sh

	Install libtools & uv. After which you can run "buildme".

	Options:
	  -h         Show this message and exit.
	  -v         Show the version and exit.

EOF

while getopts ":h" option; do

	# Parse options.
	case $option in

	# h for help.
	h)
		echo "${HELP}"
		exit 0
		;;

	# Unrecognized options set $option to '?'.
	\?)
		echo "Invalid option: -${OPTARG}"
		echo "${HELP}"
		exit 0
		;;
	
	esac

done

echo "Installing..."
curl -LsSf https://astral.sh/uv/install.sh | sh
git clone https://github.com/hunterdsp/libtools.git "${HOME}/.libtools"
ln -sf "${HOME}/buildme" "${HOME}/.libtools/buildme"
uv sync --directory "${HOME}/.libtools"
./"${HOME}/buildme" -h
echo "...done!"