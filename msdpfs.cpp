/**
    msdpfs.cpp, by Dirk Leas

    Copyright (C) 2017  Dirk Leas

    This program is free software; you may redistribute and/or modify
    it under the terms of the GNU General Public Licence as published by
    the Free Software Foundation, either version 3 of said Licence, or
    (at your option) any later version.

--

    msdpfs - filesystem exists, rm, mkdir, cp

    max-devkit api: quasi (https://tinyurl.com/khygtdf)

    macos:
    cmake ..
    cmake --build .

    windows:
    cmake -G "Visual Studio 15 2017 Win64" -DWIN64:Bool=True  ..
    cmake --build . --config Release
*/

#ifdef _WIN32
    #include <direct.h>  
#endif
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "c74_max.h"
using namespace c74::max;

struct t_msdpfs {
    t_object ob;
    void *status;
};

static t_class* this_class = nullptr;

const char* real_path(const char* f) {
    static char name[MAX_PATH_CHARS];
    path_nameconform(f, name, PATH_STYLE_SLASH, PATH_TYPE_BOOT);
    return name;
}

void* msdpfs_new(t_symbol* name, long argc, t_atom* argv) {
    t_msdpfs* self = (t_msdpfs*) object_alloc(this_class);
    self->status = outlet_new(self, "cmd status, 1=success, 0=failure");
    return self;
}

void msdpfs_free(t_msdpfs* self) {}

void msdpfs_docp(t_msdpfs* self, t_symbol* s, long argc, t_atom* argv) {
    if ((argc != 2) || (atom_gettype(&argv[0]) != A_SYM) || (atom_gettype(&argv[0]) != A_SYM)) {
        object_error((t_object*)self, "source/destination missing or incorrect type, specify valid files%s", "");
        outlet_int(self->status, 0);
        return;		
    }
    try {
        std::ifstream src(real_path(atom_getsym(&argv[0])->s_name), std::ios::binary);
        std::ofstream dst(real_path(atom_getsym(&argv[1])->s_name), std::ios::binary);
        dst << src.rdbuf();
        outlet_int(self->status, 1);
        return;
    } catch (const std::exception& e) {
        object_error((t_object*)self, "can't copy from %s to %s, invalid source or existing destination", 
            atom_getsym(&argv[0])->s_name, atom_getsym(&argv[1])->s_name);
        outlet_int(self->status, 0);
        return;
    }
}

void msdpfs_doexists(t_msdpfs* self, t_symbol* s, long argc, t_atom* argv) {
    struct stat f;
    if (stat(real_path(s->s_name), &f) == 0) outlet_int(self->status, 1);
    else {
        object_error((t_object*)self, "no such file or directory %s", s->s_name);
        outlet_int(self->status, 0);
    }
}

void msdpfs_domkdir(t_msdpfs* self, t_symbol* s, long argc, t_atom* argv) {
    int status = -1;
    struct stat f;
    if (stat(real_path(s->s_name), &f) == 0) {
        object_error((t_object*)self, "directory %s already exists", s->s_name);
        outlet_int(self->status, 0);
        return;
    }
#ifdef _WIN32
    status = _mkdir(real_path(s->s_name));
#else
    status = mkdir(real_path(s->s_name), 0777);
#endif
    if (status == 0) {
        outlet_int(self->status, 1);
        return;
    }
    else {
        object_error((t_object*)self, "can't make directory %s", s->s_name);
        outlet_int(self->status, 0);
        return;
    }
}

void msdpfs_dorm(t_msdpfs* self, t_symbol* s, long argc, t_atom* argv) {
    struct stat f;
    if (stat(real_path(s->s_name), &f) != 0) {
        object_error((t_object*)self, "no such file or directory %s", s->s_name);
        outlet_int(self->status, 0);
        return;
    }
    if (remove(real_path(s->s_name)) == 0) {
        outlet_int(self->status, 1);
        return;
    }
    else {
        object_error((t_object*)self, "can't remove file or directory %s, error %d", s->s_name, errno);
        outlet_int(self->status, 0);
        return;
    }
}

void msdpfs_cp(t_object* self, t_symbol* s, long argc, t_atom* argv) {
    defer(self, (method)msdpfs_docp, s, argc, argv);
}
void msdpfs_exists(t_object* self, t_symbol* s) { defer(self, (method)msdpfs_doexists, s, 0, NULL); }
void msdpfs_mkdir(t_object* self, t_symbol* s) { defer(self, (method)msdpfs_domkdir, s, 0, NULL); }
void msdpfs_rm(t_object* self, t_symbol* s) { defer(self, (method)msdpfs_dorm, s, 0, NULL); }

void msdpfs_assist(t_msdpfs* self, void* unused, t_assist_function io, long index, char* string_dest) {
    if (io == ASSIST_INLET) {
        switch (index) {
            case 0: 
                strncpy(string_dest,"[ cp | exists | mkdir | rm ] FILE | DIR [ FILE ]", ASSIST_STRING_MAXSIZE); 
                break;
        }
    }
    else if (io == ASSIST_OUTLET) {
        switch (index) {
            case 0: 
                strncpy(string_dest,"status, 1=success, 0=fail", ASSIST_STRING_MAXSIZE); 
                break;
        }
    }
}

void ext_main(void* r) {
    this_class = class_new("msdpfs", (method)msdpfs_new, (method)msdpfs_free, sizeof(t_msdpfs), 0L, A_GIMME, 0);
    class_addmethod(this_class, (method)msdpfs_cp, "cp", A_GIMME, 0);
    class_addmethod(this_class, (method)msdpfs_exists, "exists", A_DEFSYM, 0);
    class_addmethod(this_class, (method)msdpfs_mkdir, "mkdir", A_DEFSYM, 0);
    class_addmethod(this_class, (method)msdpfs_rm, "rm", A_DEFSYM, 0);
    class_register(CLASS_BOX, this_class);
}
