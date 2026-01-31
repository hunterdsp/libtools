#!/bin/sh
# ############################################################################
# EXECUTABLE: install.sh		  			                                 #
# PACKAGE: libtools version 0.1.0	                                         #
# ############################################################################
set -eu
OPTARG=
OPTIND=0
while getopts ":h" option; do
case $option in

h)
cat <<-'EOF'
	Usage: sudo ./install.sh

	Install libtools & uv. After which you can run "buildme".

	Options:
	  -h         Show this message and exit.
	  -v         Show the version and exit.

EOF
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
curl -LsSf https://astral.sh/uv/install.sh | sh &&
	git clone https://github.com/hunterdsp/libtools.git \
		"${HOME}/.local/share/" &&
	uv sync --directory "${HOME}/.local/share/libtools"