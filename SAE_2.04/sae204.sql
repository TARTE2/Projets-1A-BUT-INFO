CREATE TABLE _Formation (
	cod_aff_form VARCHAR(5),
  	filiere_libelle_detaille VARCHAR(66),
  	coordonnees_gps VARCHAR (21),
  	list_com VARCHAR(134),
  	concours_communs_banque_epreuve VARCHAR(98),
  	url_formation VARCHAR(91),
  	tri VARCHAR(19),
  	CONSTRAINT formation_pk PRIMARY KEY (cod_aff_form)
);

CREATE TABLE _Filiere (
	filiere_id INT,
  	filiere_libelle VARCHAR(279),
  	filiere_libelle_abrege VARCHAR(17),
  	filiere_libelle_detaille_bis VARCHAR (119),
  	CONSTRAINT filiere_pk PRIMARY KEY (filiere_id)
  	
); 

CREATE TABLE _Academie (
	academie_nom VARCHAR(19),
  	CONSTRAINT academie_pk PRIMARY KEY (academie_nom)
);

CREATE TABLE _Etablissement (
	etablissement_code_uai VARCHAR(8),
  	etablissement_nom VARCHAR(1),
  	etablissment_statut VARCHAR(32),
  	CONSTRAINT etablissement_pk PRIMARY KEY (etablissement_code_uai)
);

CREATE TABLE _Departement (
	departement_code VARCHAR(3),
  	departement_nom VARCHAR(23),
	CONSTRAINT departement_fk PRIMARY KEY(departement_code)
);

CREATE TABLE _Commune (
	commune_nom VARCHAR(29),
	departement_code VARCHAR(3),
  	CONSTRAINT commune_pk PRIMARY KEY (commune_nom, departement_code),
	CONSTRAINT commune_departement_fk FOREIGN KEY (departement_code) REFERENCES _Departement (departement_code)
);

CREATE TABLE _Region(
	region_nom VARCHAR(26),
  	CONSTRAINT region_pk PRIMARY KEY (region_nom)
  
);

CREATE TABLE _Type_bac (
	type_bac VARCHAR(1),
  	CONSTRAINT type_bac_pk PRIMARY KEY (type_bac)
);

CREATE TABLE _Admissions_generalites (
	selectivite VARCHAR(23),
  	capacite INT,
  	effectif_total_candidats INT,
  	effectif_total_candidates INT,
  	CONSTRAINT admissions_generalites_pk PRIMARY KEY (selectivite)
);

CREATE TABLE _Mention_bac (
	libelle_mention VARCHAR(17),
  	CONSTRAINT _mention_bac_pk PRIMARY KEY (libelle_mention)
);

CREATE TABLE _Regroupement (
	libelle_regroupement VARCHAR(68),
  	CONSTRAINT regroupement_pk PRIMARY KEY (libelle_regroupement)
);

CREATE TABLE _Session (
	session_annee INT,
  	CONSTRAINT session_pk PRIMARY KEY (session_annee)
);




--RELATION

--_ACADEMIE, _FORMATION
ALTER TABLE _Formation
ADD COLUMN academie_nom VARCHAR(19),
ADD CONSTRAINT formation_academie_fk
FOREIGN KEY (academie_nom)
REFERENCES _Academie (academie_nom);

--_FILIERE, _FORMATION
ALTER TABLE _Formation
ADD COLUMN filiere_id INT NOT NULL,
ADD CONSTRAINT formation_filiere_fk
FOREIGN KEY (filiere_id)
REFERENCES _Filiere (filiere_id);

--_ETABLISSEMENT, _FORMATION
ALTER TABLE _Formation
ADD COLUMN etablissement_code_uai VARCHAR(8),
ADD CONSTRAINT formation_etablissement_fk
FOREIGN KEY (etablissement_code_uai)
REFERENCES _Etablissement (etablissement_code_uai);

--_FORMATION, _COMMUNE
ALTER TABLE _Formation
ADD COLUMN commune_nom VARCHAR(29) NOT NULL,
ADD COLUMN departement_code VARCHAR(3) NOT NULL,
ADD CONSTRAINT formation_commune_fk
FOREIGN KEY (commune_nom, departement_code)
REFERENCES _Commune (commune_nom, departement_code);

--_DEPARTEMENT, _REGION
ALTER TABLE _Departement
ADD COLUMN region_nom VARCHAR(26),
ADD CONSTRAINT departement_region_fk
FOREIGN KEY (region_nom)
REFERENCES _Region (region_nom);

--CLASSE ASSOCIATION

--_FORMATION, _SESSION,_ ADMISSIONS_GENERALITES
ALTER TABLE _Admissions_generalites
ADD COLUMN formation_pk VARCHAR(5),
ADD CONSTRAINT admissions_generalites_formation_fk
FOREIGN KEY (formation_pk)
REFERENCES _Formation (cod_aff_form);
ALTER TABLE _Admissions_generalites
ADD COLUMN session_annee INT,
ADD CONSTRAINT admissions_generalites_session_fk
FOREIGN KEY (session_annee)
REFERENCES _Session (session_annee);

--ASSOCIATION TERNAIRE

--_FORMATION, _SESSION, _MENTION_BAC, _EFFECTIF_SELON_MENTION
CREATE TABLE _Effectif_selon_mention (
  formation_cod_aff_form VARCHAR(5),
  session_annee INT,
  mention_libelle VARCHAR(17),
  effectif_admis_neo_bac_selon_mention INT,
  CONSTRAINT effectif_selon_mention_pk PRIMARY KEY (formation_cod_aff_form, session_annee, mention_libelle),
  CONSTRAINT effectif_selon_mention_formation_fk FOREIGN KEY (formation_cod_aff_form) REFERENCES _Formation (cod_aff_form),
  CONSTRAINT effectif_selon_mention_session_fk FOREIGN KEY (session_annee) REFERENCES _Session (session_annee),
  CONSTRAINT effectif_selon_mention_mention_fk FOREIGN KEY (mention_libelle) REFERENCES _Mention_bac (libelle_mention)
);

--_FORMATION, _SESSION, _TYPE_BAC, _ADMISSIONS_SELON_TYPE_NEO_BAC
CREATE TABLE _Admissions_selon_type_neo_bac (
  formation_cod_aff_form VARCHAR(5),
  session_annee INT,
  type_bac VARCHAR(1),
  effectif_candidat_neo_bac_classes INT,
  CONSTRAINT admissions_selon_type_neo_bac_pk PRIMARY KEY (formation_cod_aff_form, session_annee, type_bac),
  CONSTRAINT admissions_selon_type_neo_bac_formation_fk FOREIGN KEY (formation_cod_aff_form) REFERENCES _Formation (cod_aff_form),
  CONSTRAINT admissions_selon_type_neo_bac_session_fk FOREIGN KEY (session_annee) REFERENCES _Session (session_annee),
  CONSTRAINT admissions_selon_type_neo_bac_type_bac_fk FOREIGN KEY (type_bac) REFERENCES _Type_bac (type_bac)
);



--_FORMATION, _SESSION,_REGROUPEMENT, _RANG_DERNIER_APPELE_SELON_REGROUPEMENT
CREATE TABLE _Rang_dernier_appele_selon_regroupement (
  formation_cod_aff_form VARCHAR(5),
  session_annee INT,
  regroupement_libelle VARCHAR(68),
  rang_dernier_appele INT,
  CONSTRAINT rang_dernier_appele_selon_regroupement_pk PRIMARY KEY (formation_cod_aff_form, session_annee, regroupement_libelle),
  CONSTRAINT rang_dernier_appele_selon_regroupement_formation_fk FOREIGN KEY (formation_cod_aff_form) REFERENCES _Formation (cod_aff_form),
  CONSTRAINT rang_dernier_appele_selon_regroupement_session_fk FOREIGN KEY (session_annee) REFERENCES _Session (session_annee),
  CONSTRAINT rang_dernier_appele_selon_regroupement_regroupement_fk FOREIGN KEY (regroupement_libelle) REFERENCES _Regroupement (libelle_regroupement)
);