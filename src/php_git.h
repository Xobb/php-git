/*
 * The MIT License
 *
 * Copyright (c) 2010 - 2011 Shuhei Tanuma
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef PHP_GIT_H

#define PHP_GIT_H

#define PHP_GIT_EXTNAME "git"
#define PHP_GIT_EXTVER "0.2.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/spl/spl_exceptions.h"
#include <git2.h>
#include <git2/odb_backend.h>

void php_git_throw_exception(int error,zend_class_entry *exception, INTERNAL_FUNCTION_PARAMETERS);
#define PHP_GIT_THROW_EXCEPTION(error) php_git_throw_exception(error,git_exception_class_entry,INTERNAL_FUNCTION_PARAM_PASSTHRU); \
    RETURN_FALSE;

/* Define the entry point symbol
 * Zend will use when loading this module
 */
extern zend_module_entry git_module_entry;
#define phpext_git_ptr &git_module_entry;
#define PHP_GIT_NS "Git"

extern PHPAPI zend_class_entry *git_class_entry;
extern PHPAPI zend_class_entry *git_reference_class_entry;
extern PHPAPI zend_class_entry *git_reference_manager_class_entry;
extern PHPAPI zend_class_entry *git_repository_class_entry;
extern PHPAPI zend_class_entry *git_object_class_entry;
extern PHPAPI zend_class_entry *git_index_class_entry;
extern PHPAPI zend_class_entry *git_index_iterator_class_entry;
extern PHPAPI zend_class_entry *git_index_entry_class_entry;
extern PHPAPI zend_class_entry *git_walker_class_entry;
extern PHPAPI zend_class_entry *git_tree_class_entry;
extern PHPAPI zend_class_entry *git_tree_builder_class_entry;
extern PHPAPI zend_class_entry *git_tree_iterator_class_entry;
extern PHPAPI zend_class_entry *git_tree_entry_class_entry;
extern PHPAPI zend_class_entry *git_commit_class_entry;
extern PHPAPI zend_class_entry *git_signature_class_entry;
extern PHPAPI zend_class_entry *git_tag_class_entry;
extern PHPAPI zend_class_entry *git_blob_class_entry;
extern PHPAPI zend_class_entry *git_odb_class_entry;
extern PHPAPI zend_class_entry *git_exception_class_entry;
PHPAPI zend_class_entry *git_backend_class_entry;

typedef struct{
    zend_object zo;
    git_index *index;
} php_git_index_t;

typedef struct{
    zend_object zo;
    git_index *index;
    long offset;
} php_git_index_iterator_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
} php_git_repository_t;

typedef struct{
    zend_object zo;
    git_treebuilder *builder;
    git_repository *repository;
} php_git_tree_builder_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
    git_tree_entry *entry;
} php_git_tree_entry_t;

typedef struct{
    zend_object zo;
    git_tree *tree;
    long offset;
    git_repository *repository;
} php_git_tree_iterator_t;

typedef struct{
    zend_object zo;
    git_revwalk *walker;
} php_git_walker_t;

typedef struct{
    git_odb_backend parent;
    zval *self;
} php_git_backend_internal;

typedef struct{
    zend_object zo;
    php_git_backend_internal *backend;
} php_git_backend_t;

typedef struct{
    zend_object zo;
    git_signature *signature;
} php_git_signature_t;

typedef struct{
    zend_object zo;
    git_odb *odb;
} php_git_odb_t;

typedef struct{
    zend_object zo;
    git_index_entry *object;
} php_git_index_entry_t;

typedef struct{
    zend_object zo;
    git_object *object;
} php_git_object_t;

// extends git_object
typedef struct{
    zend_object zo;
    git_commit *object;
    git_repository *repository;
} php_git_commit_t;

typedef struct{
    zend_object zo;
    git_tree *object;
    git_repository *repository;
} php_git_tree_t;

typedef struct{
    zend_object zo;
    git_tag *object;
} php_git_tag_t;

enum php_git_blob_write_type{
    PHP_GIT_LOAD_FROM_FILE,
    PHP_GIT_LOAD_FROM_STRING
};

typedef struct{
    zend_object zo;
    git_blob *object;
    git_repository *repository;
    enum php_git_blob_write_type type;
    char *contents;
    int contents_len;
} php_git_blob_t;

typedef struct{
    zend_object zo;
    git_reference *object;
} php_git_reference_t;

typedef struct{
    zend_object zo;
    git_repository *repository;
} php_git_reference_manager_t;


#endif /* PHP_GIT_H */