/* configure the network */
/* neuron groups */
int EC_LI_II_Multipolar_Pyramidal=sim.createGroup("EC_LI_II_Multipolar_Pyramidal", 
                            p.EC_LI_II_Multipolar_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);  
int MEC_LII_Stellate=sim.createGroup("MEC_LII_Stellate", 
                            p.MEC_LII_Stellate_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
int EC_LII_Axo_Axonic=sim.createGroup("EC_LII_Axo_Axonic", 
                            p.EC_LII_Axo_Axonic_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket=sim.createGroup("MEC_LII_Basket", 
                            p.MEC_LII_Basket_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int EC_LII_Basket_Multipolar=sim.createGroup("EC_LII_Basket_Multipolar", 
                            p.EC_LII_Basket_Multipolar_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int CA1_Pyramidal=sim.createGroup("CA1_Pyramidal", 
                            p.CA1_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket_Speed=sim.createGroup("MEC_LII_Basket_Speed", 
                            p.MEC_LII_Basket_Speed_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Stellate_Speed=sim.createGroup("MEC_LII_Stellate_Speed", 
                            p.MEC_LII_Stellate_Speed_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
// assign group numbers for later access
p.EC_LI_II_Multipolar_Pyramidal_Group = EC_LI_II_Multipolar_Pyramidal; // 0
p.MEC_LII_Stellate_Group = MEC_LII_Stellate; // 1
p.EC_LII_Axo_Axonic_Group = EC_LII_Axo_Axonic; // 2
p.MEC_LII_Basket_Group = MEC_LII_Basket; // 3
p.EC_LII_Basket_Multipolar_Group = EC_LII_Basket_Multipolar; // 4
p.CA1_Pyramidal_Group = CA1_Pyramidal; // 5
p.MEC_LII_Basket_Speed_Group = MEC_LII_Basket_Speed; // 6
p.MEC_LII_Stellate_Speed_Group = MEC_LII_Stellate_Speed; // 7

/* neuron type parameters */
sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 375.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
                                7.0f, 0.0f, 0); // C,k,vr,vt,a,b,vpeak,c,d
// sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
//                                 0.0f, 0.001f, 0.0f, -4.08f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
//                                 13.0f, 0.0f, 0); // C,k,vr,vt,a,b,vpeak,c,d
// sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 286.0f, 0.0f, 1.53f, 0.0f, -56.14f, 0.0f, -39.78f, 
//                                 0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 18.27f, 0.0f, -49.81f, 0.0f, 
//                                 7.0f, 0.0f, 0); // C,k,vr,vt,a,b,vpeak,c,d
                                // Ensemble file:  k,a,b,d,C,vr,vt,c,vpeak. 
                                // 1->2, 2->5, 3->6, 4->9, 5->1, 6->3, 7->4, 8->8, 9->7
// sim.setNeuronParameters(MEC_LII_Stellate, 131.000000f, 0.0f, 0.98f, 0.0f, -62.65f, 0.0f, 
//                                 -43.6f, 0.0f, 0.004f, 0.0f, -23.77f, 0.0f, 7.85f, 0.0f, 
//                                 -52.68f, 0.0f, 119.0f, 0.0f, 0);
// sim.setNeuronParameters(MEC_LII_Stellate, 131.000000f, 0.0f, 0.98f, 0.0f, -62.65f, 0.0f, 
//                                 -43.6f, 0.0f, 0.005f, 0.0f, 0.0f, 0.0f, 7.85f, 0.0f, 
//                                 -52.68f, 0.0f, 10.0f, 0.0f, 0);
// sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, 
//                                 -43.52f, 0.0f, 0.005f, 0.0f, 11.69f, 0.0f, 11.48f, 0.0f, 
//                                 -49.52f, 0.0f, 3.0f, 0.0f, 0);
// sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, 
//                                 -43.52f, 0.0f, 0.005f, 0.0f, 8.0f, 0.0f, 11.48f, 0.0f, 
//                                 -49.52f, 0.0f, 8.5f, 0.0f, 0);
sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, 
                                -43.52f, 0.0f, 0.005f, 0.0f, 11.69f, 0.0f, 11.48f, 0.0f, 
                                -49.52f, 0.0f, 0.0f, 0.0f, 0);
sim.setNeuronParameters(EC_LII_Axo_Axonic, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 0); 
sim.setNeuronParameters(MEC_LII_Basket, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 0); 
sim.setNeuronParameters(EC_LII_Basket_Multipolar, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 0); 
sim.setNeuronParameters(MEC_LII_Basket_Speed, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 0);
sim.setNeuronParameters(MEC_LII_Stellate_Speed, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, -43.52f, 
                                0.0f, 0.005f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 
                                50.0f, 0.0f, 0);
                                // C,k,vr,vt,a,b,vpeak,c,d
// sim.setNeuronParameters(CA1_Pyramidal, 204.0f, 0.0f, 0.76f, 0.0f, -69.36f, 0.0f, -39.99f, 
//                                 0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 25.46f, 0.0f, -54.95f, 
//                                 0.0f, 16.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 334.0f, 0.0f, 1.56f, 0.0f, -69.36f, 0.0f, -53.22f, 
//                                 0.0f, 0.0f, 0.0f, -17.25f, 0.0f, 25.46f, 0.0f, -60.22f, 
//                                 0.0f, 16.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
//                                 0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
//                                 7.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 1169.0f, 0.0f, 0.76f, 0.0f, -63.21f, 0.0f, -32.94f, 
//                                 0.0f, 0.001f, 0.0f, 18.93f, 0.0f, 59.92f, 0.0f, -41.15f, 
//                                 0.0f, 24.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 302.0f, 0.0f, 1.7054968952326925f, 0.0f, -69.92430397896125f, 0.0f, -57.33313161f, 
//                                 0.0f, 0.0011921182805996267f, 0.0f, -2.8383619240678364f, 0.0f, 24.88998748f, 0.0f, -60.37396346f, 
//                                 0.0f, 18.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 23.0f, 0.0f, 1.25f, 0.0f, -69.75f, 0.0f, -46.56f, 
//                                 0.0f, 0.001f, 0.0f, -38.7f, 0.0f, 24.57f, 0.0f, -54.88f, 
//                                 0.0f, 43.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 506.0f, 0.0f, 5.89f, 0.0f, -62.16f, 0.0f, -48.42f, 
//                                 0.0f, 0.081f, 0.0f, -15.09f, 0.0f, 32.77f, 0.0f, -52.21f, 
//                                 0.0f, 483.0f, 0.0f, 0);
                                // C,k,vr,vt,a,b,vpeak,c,d
sim.setNeuronParameters(CA1_Pyramidal, 530.0f, 0.0f, 1.7382527828120673f, 0.0f, -69.97816841048154f, 0.0f, -57.42740032f, 
                               0.0f, 0.0028211397234640546f, 0.0f, -0.7818603847193373f, 0.0f, 24.44743634f, 0.0f, -60.35222718f, 
                               0.0f, 25.0f, 0.0f, 0);
// sim.setNeuronParameters(CA1_Pyramidal, 528.0f, 0.0f, 1.15f, 0.0f, -50.04f, 0.0f, -46.54f, 
//                                 0.0f, 0.01f, 0.0f, -0.32f, 0.0f, 29.22f, 0.0f, -50.63f, 
//                                 0.0f, 283.0f, 0.0f, 0);

/* neuron connection parameters */
setInExcConns(&sim, &p);
double gc2inwt = p.gc_to_in_wt;
MexHatConnection* MexHatConn;
SomeToSomeConnection* SomeToSomeConn;    
sim.connect(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, "one-to-one", p.dir_to_gc_wt, 1.0f, 
            RangeDelay(1), RadiusRF(-1), SYN_FIXED, (33.082*.47*1.331314709), (20.0*.47*1.331314709)); // 0 DIR
////
float m1 = 0.370*0.8*7.63;//*3;//*0.42;//*1.320675526;//1;//1.89;//1.5;//1.2;//1;//1.2;
float m1_slow = m1*0.6120576671;
float m2 = 11.76*0.8*7.63;//*(0.005537614433/0.00681312463724531);//1;
float m2_slow = m2*0.6120576671;
p.conn_offset = 0;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, EC_LII_Axo_Axonic, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, EC_LII_Axo_Axonic, SomeToSomeConn, m1, m1_slow, SYN_FIXED);    
    //sim.connect(MEC_LII_Stellate_Speed, EC_LII_Axo_Axonic, "one-to-one", p.spdex2inwt, 1.0f, 
    //        RangeDelay(1), RadiusRF(-1), SYN_FIXED, 8.5*m1, 5.2*m1); // 0 DIR
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
//sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, "one-to-one", 1.0, 1.0f, 
//            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 33.082, 20.0f);
MexHatConn = new MexHatConnection(&p);
sim.connect(EC_LII_Axo_Axonic, MEC_LII_Stellate, MexHatConn, m2, m2_slow, SYN_FIXED); // 2 IN->GC one-to-many
////
p.conn_offset = 1;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, MEC_LII_Basket, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, MEC_LII_Basket, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
    //sim.connect(MEC_LII_Stellate_Speed, MEC_LII_Basket, "one-to-one", p.spdex2inwt, 1.0f, 
    //        RangeDelay(1), RadiusRF(-1), SYN_FIXED, 8.5*m1, 5.2*m1); // 0 DIR
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, MEC_LII_Basket, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
MexHatConn = new MexHatConnection(&p);
sim.connect(MEC_LII_Basket, MEC_LII_Stellate, MexHatConn, m2, m2_slow, SYN_FIXED); // 2 IN->GC one-to-many
////
p.conn_offset = 2;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, EC_LII_Basket_Multipolar, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, EC_LII_Basket_Multipolar, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
    //sim.connect(MEC_LII_Stellate_Speed, EC_LII_Basket_Multipolar, "one-to-one", p.spdex2inwt, 1.0f, 
    //        RangeDelay(1), RadiusRF(-1), SYN_FIXED, 8.5*m1, 5.2*m1); // 0 DIR
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Basket_Multipolar, SomeToSomeConn, m1, m1_slow, SYN_FIXED);
MexHatConn = new MexHatConnection(&p);
sim.connect(EC_LII_Basket_Multipolar, MEC_LII_Stellate, MexHatConn, m2, m2_slow, SYN_FIXED); // 2 IN->GC one-to-many
//sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
//           RangeDelay(1), RadiusRF(-1), SYN_FIXED, (71.14*0.170), (43.59*0.170)); // 3 PCs
sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
           RangeDelay(1), RadiusRF(-1), SYN_FIXED, (71.14*0.170), (43.59*0.170)); // 3 PCs
// sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
//            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 34.27, 21.0f); // 3 PCs 
/*sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 33.082, 20.0f);*/

/* STP parameters */
// Keivan data conversion: g = conductance; t_d = STPtdAMPA or STPtdGABAa; u = U; t_f = tauU; t_r = tauX; 
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1802, 0.0f),
                                     STPtauU(49.9201, 0.0f),
                                     STPtauX(152.8565, 0.0f),
                                     STPtdAMPA(3.3800, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
// sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1802, 0.0f),
//                                      STPtauU(35.73788179, 0.0f),
//                                      STPtauX(418.4899027, 0.0f),
//                                      STPtdAMPA(3.468416701, 0.0f),
//                                      STPtdNMDA(150.0, 0.0f),
//                                      STPtdGABAa(6.0, 0.0f),
//                                      STPtdGABAb(150.0, 0.0f),
//                                      STPtrNMDA(0.0f, 0.0f),
//                                      STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(3.3800, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
// sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1436820457, 0.0f),
//                                      STPtauU(44.06299214, 0.0f),
//                                      STPtauX(304.2250189, 0.0f),
//                                      STPtdAMPA(3.854910895, 0.0f),
//                                      STPtdNMDA(150.0, 0.0f),
//                                      STPtdGABAa(6.0, 0.0f),
//                                      STPtdGABAb(150.0, 0.0f),
//                                      STPtrNMDA(0.0f, 0.0f),
//                                      STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1672, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(167.6863, 0.0f), 
                                    STPtdAMPA(3.0845, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1672, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(152.8565, 0.0f), 
                                    STPtdAMPA(2.8868, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.1973, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(136.5698, 0.0f), 
                                    STPtdAMPA(2.6407, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1453, 0.0f), 
                                    STPtauU(27.3057, 0.0f), 
                                    STPtauX(420.8379, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.5605f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1513, 0.0f), 
                                    STPtauU(27.8100, 0.0f), 
                                    STPtauX(443.4992, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.4880f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.1617, 0.0f), 
                                    STPtauU(30.5434, 0.0f), 
                                    STPtauX(382.4847, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.9477f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));

if (p.spin2in_active == 1) {
sim.setSTP(MEC_LII_Basket_Speed, EC_LII_Axo_Axonic, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
}

if (p.spex2in_active == 1) {
sim.setSTP(MEC_LII_Stellate_Speed, EC_LII_Axo_Axonic, true, STPu(0.1672, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(167.6863, 0.0f), 
                                    STPtdAMPA(3.0845, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate_Speed, MEC_LII_Basket, true, STPu(0.1672, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(152.8565, 0.0f), 
                                    STPtdAMPA(2.8868, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate_Speed, EC_LII_Basket_Multipolar, true, STPu(0.1973, 0.0f), 
                                    STPtauU(49.9201, 0.0f), 
                                    STPtauX(136.5698, 0.0f), 
                                    STPtdAMPA(2.6407, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
}

/* neuron monitors */
#if monitor_voltage
    sim.setNeuronMonitor(MEC_LII_Stellate,"DEFAULT");
    sim.setNeuronMonitor(MEC_LII_Basket,"DEFAULT");
    sim.setNeuronMonitor(CA1_Pyramidal,"DEFAULT");
    //sim.setNeuronMonitor(MEC_LII_Basket_Speed,"DEFAULT");
#endif