select a.asmnm as taskname, pa.prtinsid, pa.prtnmk as objname, e.envtypab, pa.grpnmk, pa.appnmk, pa.relnmk from pacmsctl.pinsxasm pa
left join pacmsctl.asmdef a on pa.asmid = a.asmid
left join pacmsctl.prtins p on pa.prtinsid = p.prtinsid
left join pacmsctl.env    e on e.envid = p.envid