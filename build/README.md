# Why is this here?
`build/` is used to hold compiled builds that we create. We typically don't
    check these builds into version control, because they clog up commit diffs 
    and contribute to a fat commit size when pushing or pulling. So, we cordon
    off the contents of this directory by including it in our .gitignore.

One caveat to this, though, is that git doesn't let you to push an empty
    directory. But, we still want to commit the `build/` directory itself so 
    the build scripts (Makefile) work on a clean install -- hence, this file.
