version=$(sed -e 's/^.*-//' -e q VERSION )
release=$(cat conf-release)
sed -e "s/@version@/$version/" \
	-e "s/@release@/$release/" \
	< $1.template
