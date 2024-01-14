DROP DATABASE IF EXISTS famy_account;

CREATE DATABASE famy_account
WITH
OWNER = postgres
ENCODING = 'utf8'
TABLESPACE = pg_default
IS_TEMPLATE = FALSE;

\c famy_account

SET session_replication_role = 'replica';

\i extension/uuid-ossp.sql

\i table/role.sql

\i table/account.sql

\i table/permission.sql

\i table/granted_permission.sql

\i seed/role.sql

SET session_replication_role = 'origin';

\c postgres
