// This file is part of Jiffy released under the MIT license.
// See the LICENSE file for more information.

#include "jiffy.h"

ERL_NIF_TERM    atom_ok;
ERL_NIF_TERM    atom_error;
ERL_NIF_TERM    atom_null;
ERL_NIF_TERM    atom_true;
ERL_NIF_TERM    atom_false;
ERL_NIF_TERM    atom_bignum;
ERL_NIF_TERM    atom_bignum_e;
ERL_NIF_TERM    atom_bigdbl;
ERL_NIF_TERM    atom_partial;
ERL_NIF_TERM    atom_uescape;
ERL_NIF_TERM    atom_pretty;
ERL_NIF_TERM    atom_force_utf8;
ERL_NIF_TERM    atom_iter;
ERL_NIF_TERM    atom_bytes_per_iter;
ERL_NIF_TERM    atom_return_maps;
ERL_NIF_TERM    atom_return_trailer;
ERL_NIF_TERM    atom_has_trailer;
ERL_NIF_TERM    atom_nil;
ERL_NIF_TERM    atom_use_nil;
ERL_NIF_TERM    atom_null_term;
ERL_NIF_TERM    atom_escape_forward_slashes;

static int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info)
{
    jiffy_st* st = enif_alloc(sizeof(jiffy_st));
    if(st == NULL) {
        return 1;
    }

    atom_ok = make_atom(env, "ok");
    atom_error = make_atom(env, "error");
    atom_null = make_atom(env, "null");
    atom_true = make_atom(env, "true");
    atom_false = make_atom(env, "false");
    atom_bignum = make_atom(env, "bignum");
    atom_bignum_e = make_atom(env, "bignum_e");
    atom_bigdbl = make_atom(env, "bigdbl");
    atom_partial = make_atom(env, "partial");
    atom_uescape = make_atom(env, "uescape");
    atom_pretty = make_atom(env, "pretty");
    atom_force_utf8 = make_atom(env, "force_utf8");
    atom_iter = make_atom(env, "iter");
    atom_bytes_per_iter = make_atom(env, "bytes_per_iter");
    atom_return_maps = make_atom(env, "return_maps");
    atom_return_trailer = make_atom(env, "return_trailer");
    atom_has_trailer = make_atom(env, "has_trailer");
    atom_nil = make_atom(env, "nil");
    atom_use_nil = make_atom(env, "use_nil");
    atom_null_term = make_atom(env, "null_term");
    atom_escape_forward_slashes = make_atom(env, "escape_forward_slashes");

    st->res_dec = enif_open_resource_type(
            env,
            NULL,
            "decoder",
            dec_destroy,
            ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER,
            NULL
        );

    st->res_enc = enif_open_resource_type(
            env,
            NULL,
            "encoder",
            enc_destroy,
            ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER,
            NULL
        );

    *priv = (void*) st;

    return 0;
}

static int
reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info)
{
    return 0;
}

static int
upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info)
{
    return load(env, priv, info);
}

static void
unload(ErlNifEnv* env, void* priv)
{
    enif_free(priv);
    return;
}

static ErlNifFunc funcs[] =
{
    {"nif_decode_init", 2, decode_init},
    {"nif_decode_iter", 5, decode_iter},
    {"nif_encode_init", 2, encode_init},
    {"nif_encode_iter", 3, encode_iter}
};

ERL_NIF_INIT(jiffy, funcs, &load, &reload, &upgrade, &unload);
