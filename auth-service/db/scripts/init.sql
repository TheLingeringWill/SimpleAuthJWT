DROP DATABASE IF EXISTS famy_auth;

CREATE DATABASE famy_auth
WITH
OWNER = postgres
ENCODING = 'utf8'
TABLESPACE = pg_default
IS_TEMPLATE = FALSE;

\c famy_auth

SET session_replication_role = 'replica';

\i table/auth.sql

\i table/provider.sql

\i table/oauthtwo.sql

\i seed/auth.sql

SET session_replication_role = 'origin';
\c postgres
