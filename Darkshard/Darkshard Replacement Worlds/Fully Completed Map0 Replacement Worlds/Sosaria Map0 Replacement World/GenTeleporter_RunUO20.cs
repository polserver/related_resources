using System;
using System.Collections;
using Server;
using Server.Items;
using Server.Commands;

namespace Server.Commands
{
	public class GenTeleporter
	{
		public GenTeleporter()
		{
		}

		public static void Initialize()
		{
			CommandSystem.Register( "TelGen", AccessLevel.Administrator, new CommandEventHandler( GenTeleporter_OnCommand ) );
		}

		[Usage( "TelGen" )]
		[Description( "Generates world/dungeon teleporters for all facets." )]
		public static void GenTeleporter_OnCommand( CommandEventArgs e )
		{
			e.Mobile.SendMessage( "Generating teleporters, please wait." );

			int count = new TeleportersCreator().CreateTeleporters();

			count += new SHTeleporter.SHTeleporterCreator().CreateSHTeleporters();

			e.Mobile.SendMessage( "Teleporter generating complete. {0} teleporters were generated.", count );
		}

		public class TeleportersCreator
		{
			private int m_Count;
			
			public TeleportersCreator()
			{
			}

			private static Queue m_Queue = new Queue();

			public static bool FindTeleporter( Map map, Point3D p )
			{
				IPooledEnumerable eable = map.GetItemsInRange( p, 0 );

				foreach ( Item item in eable )
				{
					if ( item is Teleporter && !(item is KeywordTeleporter) && !(item is SkillTeleporter) )
					{
						int delta = item.Z - p.Z;

						if ( delta >= -12 && delta <= 12 )
							m_Queue.Enqueue( item );
					}
				}

				eable.Free();

				while ( m_Queue.Count > 0 )
					((Item)m_Queue.Dequeue()).Delete();

				return false;
			}

			public void CreateTeleporter( Point3D pointLocation, Point3D pointDestination, Map mapLocation, Map mapDestination, bool back )
			{
				if ( !FindTeleporter( mapLocation, pointLocation ) )
				{
					m_Count++;
				
					Teleporter tel = new Teleporter( pointDestination, mapDestination );

					tel.MoveToWorld( pointLocation, mapLocation );
				}

				if ( back && !FindTeleporter( mapDestination, pointDestination ) )
				{
					m_Count++;

					Teleporter telBack = new Teleporter( pointLocation, mapLocation );

					telBack.MoveToWorld( pointDestination, mapDestination );
				}
			}

			public void CreateTeleporter( int xLoc, int yLoc, int zLoc, int xDest, int yDest, int zDest, Map map, bool back )
			{
				CreateTeleporter( new Point3D( xLoc, yLoc, zLoc ), new Point3D( xDest, yDest, zDest ), map, map, back);
			}

			public void DestroyTeleporter( int x, int y, int z, Map map )
			{
				Point3D p = new Point3D( x, y, z );
				IPooledEnumerable eable = map.GetItemsInRange( p, 0 );

				foreach ( Item item in eable )
				{
					if ( item is Teleporter && !(item is KeywordTeleporter) && !(item is SkillTeleporter) && item.Z == p.Z )
						m_Queue.Enqueue( item );
				}

				eable.Free();

				while ( m_Queue.Count > 0 )
					((Item)m_Queue.Dequeue()).Delete();
			}

			public void CreateTeleportersMap( Map map )
			{
				// Pyramid
				CreateTeleporter( 5952, 87, 17, 3618, 453, 0, map, true );
				CreateTeleporter( 5953, 87, 17, 3619, 453, 0, map, true );
				CreateTeleporter( 514, 1559, 0, 5396, 127, 0, map, true );
				CreateTeleporter( 5878, 139, -13, 5983, 445, 7, map, true );
				CreateTeleporter( 5878, 140, -13, 5983, 446, 7, map, true );
				CreateTeleporter( 5984, 445, 12, 5879, 139, -8, map, true );
				CreateTeleporter( 5984, 446, 12, 5879, 140, -8, map, true );
				CreateTeleporter( 3618, 452, 5952, 86, 12, 0, map, true );
				CreateTeleporter( 3619, 452, 5953, 86, 12, 0, map, true );
				CreateTeleporter( 1156, 472, -13, 5328, 573, 7, map, true );
				CreateTeleporter( 1156, 473, -13, 5328, 574, 7, map, true );
				CreateTeleporter( 5243, 518, -13, 5338, 706, 7, map, true );
				CreateTeleporter( 5243, 519, -13, 5338, 707, 7, map, true );
				CreateTeleporter( 5329, 573, 12, 1157, 472, -8, map, true );
				CreateTeleporter( 5329, 574, 12, 1157, 473, -8, map, true );
				CreateTeleporter( 5339, 706, 12, 5244, 518, -8, map, true );
				CreateTeleporter( 5339, 707, 12, 5244, 519, -8, map, true );
				CreateTeleporter( 5376, 748, -13, 5359, 908, 7, map, true );
				CreateTeleporter( 5360, 908, 12, 5377, 748, -8, map, true );
				CreateTeleporter( 5360, 909, 12, 5377, 749, -8, map, true );
				CreateTeleporter( 5376, 749, -13, 5359, 909, 7, map, true );
				
				// Mage Keep Portal
				CreateTeleporter( 1826, 760, 0, 1824, 760, 20, map, true );
				
				// Dardin
				CreateTeleporter( 5697, 53, 17, 3005, 442, 0, map, true );
				CreateTeleporter( 5698, 53, 17, 3006, 442, 0, map, true );
				CreateTeleporter( 5646, 148, -13, 5779, 390, 7, map, true );
				CreateTeleporter( 5646, 149, -13, 5779, 391, 7, map, true );
				CreateTeleporter( 3005, 441, 5697, 52, 12, 0, map, true );
				CreateTeleporter( 3006, 441, 5698, 52, 12, 0, map, true );
				CreateTeleporter( 5780, 390, 12, 5647, 148, -8, map, true );
				CreateTeleporter( 5780, 391, 12, 5647, 149, -8, map, true );
				
				// Doom
				CreateTeleporter( 1622, 2562, 5324, 72, 7, 0, map, true );
				CreateTeleporter( 1622, 2561, 5324, 71, 7, 0, map, true );
				CreateTeleporter( 5398, 299, 12, 5212, 85, -8, map, true );
				CreateTeleporter( 5398, 298, 12, 5212, 84, -8, map, true );
				CreateTeleporter( 5325, 72, 12, 1623, 2562, 0, map, true );
				CreateTeleporter( 5325, 71, 12, 1623, 2561, 0, map, true );
				CreateTeleporter( 5211, 85, -13, 5397, 299, 7, map, true );
				CreateTeleporter( 5211, 84, -13, 5397, 298, 7, map, true );
				
				// Unknown cave
				CreateTeleporter( 1318, 3602, 45, 2994, 3696, 0, map, true );
				CreateTeleporter( 1318, 3603, 45, 2994, 3697, 0, map, true );
				CreateTeleporter( 2995, 3696, 0, 1319, 3602, 45, map, true );
				CreateTeleporter( 2995, 3697, 0, 1319, 3603, 45, map, true );

				// Clues
				CreateTeleporter( 5556, 2183, 12, 5406, 2340, -8, map, true );
				CreateTeleporter( 5557, 2183, 12, 5407, 2340, -8, map, true );
				CreateTeleporter( 5989, 2187, 12, 5704, 2173, -8, map, true );
				CreateTeleporter( 5990, 2187, 12, 5705, 2173, -8, map, true );
				CreateTeleporter( 3759, 2034, 0, 5313, 2277, 0, map, true );
				CreateTeleporter( 3760, 2034, 0, 5314, 2277, 0, map, true );
				CreateTeleporter( 5704, 2172, -13, 5989, 2186, 7, map, true );
				CreateTeleporter( 5705, 2172, -13, 5990, 2186, 7, map, true );
				CreateTeleporter( 5313, 2278, 0, 3759, 2035, 0, map, true );
				CreateTeleporter( 5314, 2278, 0, 3760, 2035, 0, map, true );
				CreateTeleporter( 5406, 2339, -13, 5556, 2182, 7, map, true );
				CreateTeleporter( 5407, 2339, -13, 5557, 2182, 7, map, true );

				// Time
				CreateTeleporter( 5630, 602, 17, 3831, 1488, 0, map, true ); 
				CreateTeleporter( 5631, 602, 17, 3832, 1488, 0, map, true );
				CreateTeleporter( 5573, 690, -13, 5560, 923, 7, map, true ); 
				CreateTeleporter( 5574, 690, -13, 5561, 923, 7, map, true );
				CreateTeleporter( 5560, 924, 12, 5573, 691, -8, map, true );
				CreateTeleporter( 5561, 924, 12, 5574, 691, -8, map, true );
				CreateTeleporter( 3831, 1487, 0, 5630, 601, 12, map, true );
				CreateTeleporter( 3832, 1487, 0, 5631, 601, 12, map, true );

				// King Crypt

				CreateTeleporter( 3063, 958, -22, 5213, 1842, 12, map, true );
				CreateTeleporter( 3064, 958, -22, 5214, 1842, 12, map, true );
				CreateTeleporter( 5213, 1843, 12, 3063, 959, -20, map, true );
				CreateTeleporter( 5214, 1843, 12, 3064, 959, -20, map, true );

				// TP Caves
				CreateTeleporter( 4180, 267, 0, 5180, 1760, 0, map, true );
				CreateTeleporter( 4181, 267, 0, 5181, 1760, 0, map, true );
				CreateTeleporter( 2508, 936, 0, 5702, 2370, 0, map, true );
				CreateTeleporter( 2509, 936, 0, 5703, 2370, 0, map, true );
				CreateTeleporter( 1000, 573, 0, 5672, 2490, 0, map, true );
				CreateTeleporter( 1001, 573, 0, 5673, 2490, 0, map, true );
				CreateTeleporter( 5702, 2371, 0, 2508, 937, 0, map, true );
				CreateTeleporter( 5703, 2371, 0, 2509, 937, 0, map, true );
				CreateTeleporter( 5672, 2491, 0, 1000, 574, 0, map, true );
				CreateTeleporter( 5673, 2491, 0, 1001, 574, 0, map, true ); 
				CreateTeleporter( 5329, 2512, 0, 2568, 2622, 0, map, true ); 
				CreateTeleporter( 5330, 2512, 0, 2569, 2622, 0, map, true ); 
				CreateTeleporter( 5424, 2515, 0, 2611, 2623, 0, map, true ); 
				CreateTeleporter( 5425, 2515, 0, 2612, 2623, 0, map, true ); 
				CreateTeleporter( 2568, 2621, 0, 5329, 2511, 0, map, true );
				CreateTeleporter( 2569, 2621, 0, 5330, 2511, 0, map, true ); 
				CreateTeleporter( 2611, 2622, 0, 5424, 2514, 0, map, true ); 
				CreateTeleporter( 2612, 2622, 0, 5425, 2514, 0, map, true );
				CreateTeleporter( 1889, 1453, 2, 5351, 1711, 0, map, true );
				CreateTeleporter( 1890, 1453, 2, 5352, 1711, 0, map, true ); 
				CreateTeleporter( 1555, 1405, 2, 5247, 1572, 0, map, true ); 
				CreateTeleporter( 1555, 1406, 2, 5247, 1573, 0 , map, true );
				CreateTeleporter( 3231, 1581, 0, 3204, 3692, 0, map, true ); 
				CreateTeleporter( 3232, 1581, 0, 3205, 3692, 0, map, true ); 
				CreateTeleporter( 5248, 1572, 0, 1556, 1405, 2, map, true ); 
				CreateTeleporter( 5248, 1573, 0, 1556, 1406, 2, map, true ); 
				CreateTeleporter( 3272, 1693, 0, 3307, 3818, 0, map, true ); 
				CreateTeleporter( 3273, 1693, 0, 3308, 3818, 0, map, true ); 
				CreateTeleporter( 5351, 1712, 0, 1889, 1454, 2, map, true ); 
				CreateTeleporter( 5352, 1712, 0, 1890, 1454, 2, map, true ); 
				CreateTeleporter( 5461, 1704, 0, 1841, 2209, 0, map, true ); 
				CreateTeleporter( 5462, 1704, 0, 1842, 2209, 0, map, true ); 
				CreateTeleporter( 5180, 1761, 0, 4180, 268, 0, map, true ); 
				CreateTeleporter( 5181, 1761, 0, 4181, 268, 0, map, true );
				CreateTeleporter( 1841, 2208, 0, 5461, 1703, 0, map, true ); 
				CreateTeleporter( 1842, 2208, 0, 5462, 1703, 0, map, true );
				CreateTeleporter( 3204, 3693, 0, 3231, 1582, 0, map, true ); 
				CreateTeleporter( 3205, 3693, 0, 3232, 1582, 0, map, true ); 
				CreateTeleporter( 3307, 3819, 0, 3272, 1694, 0, map, true ); 
				CreateTeleporter( 3308, 3819, 0, 3273, 1694, 0, map, true );

				// IronBlood
				CreateTeleporter( 4702, 1206, 5, 5430, 2889, 25, map, true );
				CreateTeleporter( 5430, 2890, 25, 4702, 1207, 5, map, true );
				CreateTeleporter( 4703, 1206, 5, 5431, 2889, 25, map, true );
				CreateTeleporter( 5431, 2890, 25, 4703, 1207, 5, map, true );

				// Underhill
				CreateTeleporter( 4459, 1263, 5, 4307, 3483, 25, map, true );
				CreateTeleporter( 4307, 3484, 25, 4459, 1264, 5, map, true );
				CreateTeleporter( 4460, 1263, 5, 4308, 3483, 25, map, true );
				CreateTeleporter( 4308, 3484, 25, 4460, 1264, 5, map, true );

				// Perin Depths
				CreateTeleporter( 4738, 1323, 5, 4309, 3827, 12, map, true );
				CreateTeleporter( 4310, 3827, 17, 4739, 1323, 5, map, true );
				CreateTeleporter( 4738, 1324, 5, 4309, 3828, 12, map, true );
				CreateTeleporter( 4310, 3828, 17, 4739, 1324, 5, map, true );
				CreateTeleporter( 4808, 1273, 5, 4401, 3684, 12, map, true );
				CreateTeleporter( 4401, 3685, 17, 4808, 1274, 5, map, true );
				CreateTeleporter( 4809, 1273, 5, 4402, 3684, 12, map, true );
				CreateTeleporter( 4402, 3685, 17, 4809, 1274, 5, map, true );

				// Isle Cave
				CreateTeleporter( 4789, 1290, 5, 3874, 3764, 0, map, true );
				CreateTeleporter( 3875, 3764, 0, 4790, 1290, 5, map, true );
				CreateTeleporter( 4789, 1291, 5, 3874, 3765, 0, map, true );
				CreateTeleporter( 3875, 3765, 0, 4790, 1291, 5, map, true );
				CreateTeleporter( 4876, 1234, 5, 3988, 3768, 0, map, true );
				CreateTeleporter( 3988, 3769, 0, 4876, 1235, 5, map, true );
				CreateTeleporter( 4877, 1234, 5, 3989, 3768, 0, map, true );
				CreateTeleporter( 3989, 3769, 0, 4877, 1235, 5, map, true );
				CreateTeleporter( 5004, 1262, 5, 3690, 3823, 0, map, true );
				CreateTeleporter( 3690, 3824, 0, 5004, 1263, 5, map, true );
				CreateTeleporter( 5005, 1262, 5, 3691, 3823, 0, map, true );
				CreateTeleporter( 3691, 3824, 0, 5005, 1263, 5, map, true );
				CreateTeleporter( 5049, 1217, 30, 3721, 3709, 0, map, true );
				CreateTeleporter( 3721, 3710, 0, 5049, 1218, 30, map, true );
				CreateTeleporter( 5050, 1217, 30, 3722, 3709, 0, map, true );
				CreateTeleporter( 3722, 3710, 0, 5050, 1218, 30, map, true );
				CreateTeleporter( 5064, 1204, 5, 3900, 3694, 0, map, true );
				CreateTeleporter( 3901, 3694, 0, 5065, 1204, 5, map, true );
				CreateTeleporter( 5064, 1205, 5, 3900, 3695, 0, map, true );
				CreateTeleporter( 3901, 3695, 0, 5065, 1205, 5, map, true );
				CreateTeleporter( 4634, 1219, 5, 4012, 3710, 0, map, true );
				CreateTeleporter( 4012, 3711, 0, 4634, 1220, 5, map, true );
				CreateTeleporter( 4635, 1219, 5, 4013, 3710, 0, map, true );
				CreateTeleporter( 4013, 3711, 0, 4635, 1220, 5, map, true );

				// Town Load British
				CreateTeleporter( 3068, 1030, -21, 3068, 1030, 0, map, true );

				// Ed Portal
				CreateTeleporter( 5931, 569, 0, 5880, 665, 0, map, true );
				CreateTeleporter( 5881, 665, 0, 5931, 568, 0, map, true );

				// Catacombs
				CreateTeleporter( 4036, 3343, 37, 1524, 3598, 0, map, true );
				CreateTeleporter( 4036, 3344, 37, 1524, 3599, 0, map, true );
				CreateTeleporter( 3913, 3482, 37, 1382, 3641, 42, map, true );
				CreateTeleporter( 1383, 3641, 31, 3914, 3482, 26, map, true );
				CreateTeleporter( 1523, 3598, 0, 4035, 3343, 32, map, true );
				CreateTeleporter( 1523, 3599, 0, 4035, 3344, 32, map, true );

				// Underhill
				CreateTeleporter( 4601, 1229, 5, 4449, 3449, 25, map, true );
				CreateTeleporter( 4450, 3449, 25, 4602, 1229, 5, map, true );
				CreateTeleporter( 4601, 1230, 5, 4449, 3450, 25, map, true );
				CreateTeleporter( 4450, 3450, 25, 4602, 1230, 5, map, true );

				// Ratman Lair 
				CreateTeleporter( 4456, 1218, 5, 4470, 3284, 25, map, true );
				CreateTeleporter( 4471, 3284, 25, 4457, 1218, 5, map, true );
				CreateTeleporter( 4456, 1219, 5, 4470, 3285, 25, map, true );
				CreateTeleporter( 4471, 3285, 25, 4457, 1219, 5, map, true );
				CreateTeleporter( 4445, 3298, -13, 4324, 3297, 12, map, true );
				CreateTeleporter( 4325, 3297, 17, 4446, 3298, -8, map, true );
				CreateTeleporter( 4445, 3299, -13, 4324, 3298, 12, map, true );
				CreateTeleporter( 4325, 3298, 17, 4446, 3299, -8, map, true );

				// Sephiroth
				CreateTeleporter( 4628, 1348, 5, 5186, 2958, 25, map, true );
				CreateTeleporter( 5186, 2959, 25, 4628, 1349, 5, map, true );
				CreateTeleporter( 4629, 1348, 5, 5187, 2958, 25, map, true );
				CreateTeleporter( 5187, 2959, 25, 4629, 1349, 5, map, true );
				
				// Exodus Dungeon
				CreateTeleporter( 876, 2650, -13, 5931, 590, 7, map, true );
				CreateTeleporter( 876, 2651, -13, 5931, 591, 7, map, true );
				CreateTeleporter( 5932, 590, 12, 877, 2650, -8, map, true );
				CreateTeleporter( 5932, 591, 12, 877, 2651, -8, map, true );
				
				// Ice Caves
				CreateTeleporter( 5539, 2798, 0, 4396, 1262, 5, map, true );
				CreateTeleporter( 4396, 1261, 5, 5539, 2797, 0, map, true );
				CreateTeleporter( 5540, 2798, 0, 4397, 1262, 5, map, true );
				CreateTeleporter( 4397, 1261, 5, 5540, 2797, 0, map, true );
				CreateTeleporter( 5576, 2779, 0, 4433, 1243, 5, map, true );
				CreateTeleporter( 4433, 1242, 5, 5576, 2778, 0, map, true );
				CreateTeleporter( 5577, 2779, 0, 4434, 1243, 5, map, true );
				CreateTeleporter( 4434, 1242, 5, 5577, 2778, 0, map, true );
				CreateTeleporter( 5568, 2738, 0, 4425, 1202, 5, map, true );
				CreateTeleporter( 4424, 1202, 5, 5567, 2738, 0, map, true );
				CreateTeleporter( 5568, 2739, 0, 4425, 1203, 5, map, true );
				CreateTeleporter( 4424, 1203, 5, 5567, 2739, 0, map, true );
				
				// Fires of Hell
				CreateTeleporter( 5242, 1102, -13, 5362, 1348, 7, map, true );
				CreateTeleporter( 5242, 1103, -13, 5362, 1349, 7, map, true );
				CreateTeleporter( 5332, 1293, 0, 3344, 1643, 0, map, true );
				CreateTeleporter( 5333, 1293, 0, 3345, 1643, 0, map, true );
				CreateTeleporter( 5606, 1317, 12, 5361, 1397, -8, map, true );
				CreateTeleporter( 5607, 1317, 12, 5362, 1397, -8, map, true );
				CreateTeleporter( 5363, 1348, 12, 5243, 1102, -8, map, true );
				CreateTeleporter( 5363, 1349, 12, 5243, 1103, -8, map, true );
				CreateTeleporter( 5361, 1396, -13, 5606, 1316, 7, map, true );
				CreateTeleporter( 5362, 1396, -13, 5607, 1316, 7, map, true );
				CreateTeleporter( 3344, 1642, 0, 5332, 1292, 0, map, true );
				CreateTeleporter( 3345, 1642, 0, 5333, 1292, 0, map, true );
				
				// Mines of Morinia
				CreateTeleporter( 5832, 944, -13, 5916, 1316, 7, map, true );
				CreateTeleporter( 5832, 945, -13, 5916, 1317, 7, map, true );
				CreateTeleporter( 5897, 1226, 0, 1021, 1366, 2, map, true );
				CreateTeleporter( 5898, 1226, 0, 1022, 1366, 2, map, true );
				CreateTeleporter( 5917, 1316, 12, 5833, 944, -8, map, true );
				CreateTeleporter( 5917, 1317, 12, 5833, 945, -8, map, true );
				CreateTeleporter( 1021, 1365, 2, 5897, 1225, 0, map, true );
				CreateTeleporter( 1022, 1365, 2, 5898, 1225, 0, map, true );
				CreateTeleporter( 5702, 1472, 12, 5882, 1608, -7, map, true );
				CreateTeleporter( 5702, 1473, 12, 5882, 1609, -7, map, true );
				CreateTeleporter( 5881, 1608, -12, 5701, 1472, 7, map, true );
				CreateTeleporter( 5881, 1609, -12, 5701, 1473, 7, map, true );
				
			}

			public void CreateTeleportersMap2( Map map )
			{
				/*
				*/

				// Dungeon of rock
				CreateTeleporter( 2186, 294, -27, 2186, 33, -27, map, true );
				CreateTeleporter( 2187, 294, -27, 2187, 33, -27, map, true );
				CreateTeleporter( 2188, 294, -27, 2188, 33, -27, map, true );
				CreateTeleporter( 2189, 294, -27, 2189, 33, -27, map, true );
				CreateTeleporter( 2189, 320, -7, 1788, 569, 74, map, true );
				CreateTeleporter( 2188, 320, -7, 1787, 569, 74, map, true );
				CreateTeleporter( 2187, 320, -7, 1787, 569, 74, map, false );

				// Spider Cave
				DestroyTeleporter( 1783, 993, -28, map );
				DestroyTeleporter( 1784, 993, -28, map );
				DestroyTeleporter( 1785, 993, -28, map );
				DestroyTeleporter( 1786, 993, -28, map );
				DestroyTeleporter( 1787, 993, -28, map );
				DestroyTeleporter( 1788, 993, -28, map );

				DestroyTeleporter( 1419, 910, -10, map );
				DestroyTeleporter( 1420, 910, -10, map );
				DestroyTeleporter( 1421, 910, -10, map );
				DestroyTeleporter( 1422, 910, -10, map );

				CreateTeleporter( 1419, 909, -10, 1784, 994, -28, map, true );
				CreateTeleporter( 1420, 909, -10, 1785, 994, -28, map, true );
				CreateTeleporter( 1421, 909, -10, 1786, 994, -28, map, true );
				CreateTeleporter( 1787, 994, -28, 1421, 909, -10, map, false );
				CreateTeleporter( 1788, 994, -28, 1421, 909, -10, map, false );
				CreateTeleporter( 1783, 994, -28, 1419, 909, -10, map, false );

				CreateTeleporter( 1861, 980, -28, 1490, 877, 10, map, true );
				CreateTeleporter( 1861, 981, -28, 1490, 878, 10, map, true );
				CreateTeleporter( 1861, 982, -28, 1490, 879, 10, map, true );
				CreateTeleporter( 1861, 983, -28, 1490, 880, 10, map, true );
				CreateTeleporter( 1861, 984, -28, 1490, 880, 10, map, false );
				CreateTeleporter( 1516, 879, 10, 1363, 1105, -26, map, true );

				// Spectre Dungeon
				CreateTeleporter( 1362, 1031, -13, 1981, 1107, -16, map, true );
				CreateTeleporter( 1363, 1031, -13, 1982, 1107, -16, map, true );
				CreateTeleporter( 1364, 1031, -13, 1983, 1107, -16, map, true );
				CreateTeleporter( 1980, 1107, -16, 1362, 1031, -13, map, false );
				CreateTeleporter( 1984, 1107, -16, 1364, 1031, -13, map, false );

				// BLOOD DUNGEON
				CreateTeleporter( 1745, 1236, -30, 2112, 829, -11, map, true );
				CreateTeleporter( 1746, 1236, -30, 2113, 829, -11, map, true );
				CreateTeleporter( 1747, 1236, -30, 2114, 829, -11, map, true );
				CreateTeleporter( 1748, 1236, -30, 2115, 829, -11, map, true );
				CreateTeleporter( 2116, 829, -11, 1748, 1236, -30, map, false );

				// Mushroom Cave
				CreateTeleporter( 1456, 1328, -27, 1479, 1494, -28, map, true );
				CreateTeleporter( 1456, 1329, -27, 1479, 1495, -28, map, true );
				CreateTeleporter( 1456, 1330, -27, 1479, 1496, -28, map, true );
				CreateTeleporter( 1479, 1493, -28, 1456, 1328, -27, map, false );
				CreateTeleporter( 1479, 1497, -28, 1456, 1330, -27, map, false );

				// RATMAN CAVE
				CreateTeleporter( 1029, 1155, -24, 1349, 1512, -3, map, true );
				CreateTeleporter( 1029, 1154, -24, 1349, 1511, -3, map, true );
				CreateTeleporter( 1029, 1153, -24, 1349, 1510, -3, map, true );
				CreateTeleporter( 1349, 1509, -3, 1030, 1153, -24, map, false );
				CreateTeleporter( 1268, 1508, -28, 1250, 1508, -28, map, true );
				CreateTeleporter( 1268, 1509, -28, 1250, 1509, -28, map, true );
				CreateTeleporter( 1268, 1510, -28, 1250, 1510, -28, map, true );
				CreateTeleporter( 1250, 1511, -28, 1268, 1510, -28, map, false );
				CreateTeleporter( 1250, 1512, -28, 1268, 1510, -28, map, false );

				// Serpentine Passage
				DestroyTeleporter( 532, 1532, -7, map );
				DestroyTeleporter( 533, 1532, -7, map );
				DestroyTeleporter( 534, 1532, -7, map );

				CreateTeleporter( 810, 874, -39, 532, 1532, -7, map, false ); 
				CreateTeleporter( 811, 874, -39, 533, 1532, -7, map, false ); 
				CreateTeleporter( 812, 874, -39, 534, 1532, -7, map, false ); 
				CreateTeleporter( 531, 1533, -4, 810, 875, -40, map, false ); 
				CreateTeleporter( 532, 1533, -4, 811, 875, -39, map, false ); 
				CreateTeleporter( 533, 1533, -4, 812, 875, -39, map, false ); 
				CreateTeleporter( 534, 1533, -4, 813, 875, -40, map, false ); 

				CreateTeleporter( 393, 1587, -13, 78, 1366, -36, map, false ); 
				CreateTeleporter( 394, 1587, -13, 79, 1366, -36, map, false ); 
				CreateTeleporter( 395, 1587, -13, 80, 1366, -36, map, false ); 
				CreateTeleporter( 396, 1587, -13, 81, 1366, -36, map, false ); 
				CreateTeleporter( 78, 1365, -41, 393, 1586, -16, map, false ); 
				CreateTeleporter( 79, 1365, -41, 394, 1586, -16, map, false ); 
				CreateTeleporter( 80, 1365, -41, 395, 1586, -16, map, false ); 
				CreateTeleporter( 81, 1365, -41, 396, 1586, -16, map, false );
				DestroyTeleporter( 82, 1365, -38, map );

				// ANKH DUNGEON
				DestroyTeleporter( 4, 1267, -11, map );
				DestroyTeleporter( 4, 1268, -11, map );
				DestroyTeleporter( 4, 1269, -11, map );
				CreateTeleporter( 668, 928, -84, 3, 1267, -8, map, true );
				CreateTeleporter( 668, 929, -84, 3, 1268, -8, map, true );
				CreateTeleporter( 668, 930, -82, 3, 1269, -8, map, true );

				DestroyTeleporter( 154, 1473, -8, map );
				DestroyTeleporter( 155, 1473, -8, map );
				DestroyTeleporter( 156, 1473, -8, map );
				CreateTeleporter( 575, 1156, -121, 154, 1473, -8, map, false ); 
				CreateTeleporter( 576, 1156, -121, 155, 1473, -8, map, false ); 
				CreateTeleporter( 577, 1156, -121, 156, 1473, -8, map, false ); 
				CreateTeleporter( 154, 1472, -8, 575, 1155, -121, map, false ); 
				CreateTeleporter( 155, 1472, -8, 576, 1155, -120, map, false ); 
				CreateTeleporter( 156, 1472, -8, 577, 1155, -120, map, false ); 

				DestroyTeleporter( 10, 1518, -28, map );
				DestroyTeleporter( 10, 1518, -27, map );
				DestroyTeleporter( 10, 1518, -27, map );
				CreateTeleporter( 10, 872, -28, 10, 1518, -27, map, false ); 
				CreateTeleporter( 11, 872, -28, 11, 1518, -28, map, false ); 
				CreateTeleporter( 12, 872, -27, 12, 1518, -28, map, false ); 
				CreateTeleporter( 10, 1519, -28, 10, 873, -28, map, false ); 
				CreateTeleporter( 11, 1519, -27, 11, 873, -28, map, false ); 
				CreateTeleporter( 12, 1519, -27, 12, 873, -27, map, false );

				// Ratman Lair 
				CreateTeleporter( 636, 813, -62, 164, 743, -28, map, false ); 
				CreateTeleporter( 164, 746, -16, 636, 815, -52, map, false ); 

				// WISP DUNGEON
				CreateTeleporter( 348, 1427, 15, 18, 1198, -5, map, true );
				CreateTeleporter( 349, 1427, 15, 19, 1198, -5, map, true );
				CreateTeleporter( 350, 1427, 15, 20, 1198, -5, map, true );
				CreateTeleporter( 351, 1427, 15, 21, 1198, -5, map, true );
				CreateTeleporter( 712, 1490, -3, 686, 1490, -28, map, false );
				CreateTeleporter( 712, 1491, -3, 686, 1491, -28, map, false );
				CreateTeleporter( 712, 1492, -3, 686, 1492, -28, map, false );
				CreateTeleporter( 712, 1493, -3, 686, 1493, -28, map, false );
				CreateTeleporter( 694, 1490, -53, 719, 1490, -28, map, false );
				CreateTeleporter( 694, 1491, -53, 719, 1491, -28, map, false );
				CreateTeleporter( 694, 1492, -53, 719, 1492, -28, map, false );
				CreateTeleporter( 694, 1493, -53, 719, 1493, -28, map, false );
				CreateTeleporter( 775, 1467, -28, 658, 1498, -28, map, false );
				DestroyTeleporter( 658, 1498, -28, map );
				CreateTeleporter( 838, 1550, -6, 728, 1505, -28, map, false );
				CreateTeleporter( 838, 1551, -6, 728, 1506, -28, map, false );
				CreateTeleporter( 838, 1552, -6, 728, 1507, -28, map, false );
				CreateTeleporter( 838, 1553, -6, 728, 1508, -28, map, false );
				CreateTeleporter( 722, 1505, -53, 833, 1550, -28, map, false );
				CreateTeleporter( 722, 1506, -53, 833, 1551, -28, map, false );
				CreateTeleporter( 722, 1507, -53, 833, 1552, -28, map, false );
				CreateTeleporter( 722, 1508, -53, 833, 1553, -28, map, false );
				CreateTeleporter( 954, 1425, -53, 874, 1490, 2, map, false );
				CreateTeleporter( 954, 1426, -53, 874, 1491, 2, map, false );
				CreateTeleporter( 954, 1427, -53, 874, 1492, 2, map, false );
				CreateTeleporter( 954, 1428, -53, 874, 1493, 2, map, false );
				CreateTeleporter( 954, 1429, -53, 874, 1493, 2, map, false );
				CreateTeleporter( 879, 1490, 24, 960, 1425, -28, map, false );
				CreateTeleporter( 879, 1491, 24, 960, 1426, -28, map, false );
				CreateTeleporter( 879, 1492, 24, 960, 1427, -28, map, false );
				CreateTeleporter( 879, 1493, 24, 960, 1428, -28, map, false );
				CreateTeleporter( 948, 1464, -56, 951, 1442, -6, map, true );
				CreateTeleporter( 948, 1465, -56, 951, 1443, -6, map, true );
				CreateTeleporter( 948, 1466, -56, 951, 1444, -6, map, true );
				CreateTeleporter( 948, 1467, -56, 951, 1445, -6, map, true );
				CreateTeleporter( 871, 1433, -6, 897, 1449, -28, map, false );
				CreateTeleporter( 871, 1434, -6, 897, 1450, -28, map, false );
				CreateTeleporter( 871, 1435, -6, 897, 1451, -28, map, false );
				CreateTeleporter( 871, 1436, -6, 897, 1452, -28, map, false );
				CreateTeleporter( 871, 1437, -6, 897, 1453, -28, map, false );
				CreateTeleporter( 892, 1449, -51, 866, 1433, -28, map, false );
				CreateTeleporter( 892, 1450, -51, 866, 1434, -28, map, false );
				CreateTeleporter( 892, 1451, -51, 866, 1435, -28, map, false );
				CreateTeleporter( 892, 1452, -51, 866, 1436, -28, map, false );
				CreateTeleporter( 892, 1453, -51, 866, 1437, -28, map, false );
				CreateTeleporter( 812, 1546, -6, 848, 1434, -28, map, false );
				CreateTeleporter( 812, 1547, -6, 848, 1435, -28, map, false );
				CreateTeleporter( 812, 1548, -6, 848, 1436, -28, map, false );
				CreateTeleporter( 812, 1549, -6, 848, 1437, -28, map, false );
				CreateTeleporter( 843, 1434, -51, 807, 1546, -28, map, false );
				CreateTeleporter( 843, 1435, -51, 807, 1547, -28, map, false );
				CreateTeleporter( 843, 1436, -51, 807, 1548, -28, map, false );
				CreateTeleporter( 843, 1437, -51, 807, 1549, -28, map, false );
				CreateTeleporter( 751, 1473, -28, 763, 1479, -28, map, false );
				DestroyTeleporter( 763, 1479, -28, map );
				CreateTeleporter( 751, 1479, -28, 763, 1555, -28, map, false );
				DestroyTeleporter( 763, 1555, -28, map );
				CreateTeleporter( 752, 1549, -28, 751, 1484, -28, map, false );
				DestroyTeleporter( 751, 1484, -28, map );
				CreateTeleporter( 775, 1492, -28, 827, 1515, -28, map, false );
				DestroyTeleporter( 827, 1515, -28, map );
				DestroyTeleporter( 1013, 1506, 0, map );
				DestroyTeleporter( 1013, 1507, 0, map );
				DestroyTeleporter( 1013, 1508, 0, map );
				DestroyTeleporter( 1013, 1509, 0, map );
				CreateTeleporter( 904, 1360, -21, 1014, 1506, 0, map, true ); 
				CreateTeleporter( 904, 1361, -21, 1014, 1507, 0, map, true ); 
				CreateTeleporter( 904, 1362, -21, 1014, 1508, 0, map, true ); 
				CreateTeleporter( 904, 1363, -21, 1014, 1509, 0, map, true );

				/*CreateTeleporter( 650, 1297, -58, 626, 1526, -28, map, true );
				CreateTeleporter( 651, 1297, -58, 627, 1526, -28, map, true );
				CreateTeleporter( 652, 1297, -58, 628, 1526, -28, map, true );
				CreateTeleporter( 653, 1297, -58, 629, 1526, -28, map, true );*/

				// Update: remove old teleporters
				DestroyTeleporter( 650, 1297, -58, map );
				DestroyTeleporter( 651, 1297, -58, map );
				DestroyTeleporter( 652, 1297, -58, map );
				DestroyTeleporter( 653, 1297, -58, map );
				DestroyTeleporter( 626, 1526, -28, map );
				DestroyTeleporter( 627, 1526, -28, map );
				DestroyTeleporter( 628, 1526, -28, map );
				DestroyTeleporter( 629, 1526, -28, map );

				// Update: add new ones
				for ( int i = 0; i < 4; ++i )
				{
					CreateTeleporter( 650 + i, 1297, -58, 626 + i, 1526, -28, map, false );
					CreateTeleporter( 626 + i, 1527, -28, 650 + i, 1298, i == 1 ? -59 : -58, map, false );
				}

				// WISP DUNGEON MAZE
				CreateTeleporter( 747, 1539, -28, 785, 1514, -28, map, false );
				CreateTeleporter( 785, 1524, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 747, 1555, -28, 785, 1570, -28, map, false );
				CreateTeleporter( 784, 1580, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1548, -28, 781, 1547, -28, map, false );
				CreateTeleporter( 782, 1550, -28, 783, 1538, -28, map, false );
				CreateTeleporter( 783, 1539, -28, 787, 1542, -28, map, false );
				CreateTeleporter( 787, 1543, -28, 781, 1554, -28, map, false );
				CreateTeleporter( 781, 1555, -28, 789, 1556, -28, map, false );
				CreateTeleporter( 789, 1557, -28, 785, 1550, -28, map, false );
				CreateTeleporter( 784, 1550, -28, 777, 1554, -28, map, false );
				CreateTeleporter( 778, 1554, -28, 787, 1538, -28, map, false );
				CreateTeleporter( 787, 1537, -28, 781, 1546, -28, map, false );
				CreateTeleporter( 781, 1545, -28, 789, 1552, -28, map, false );
				CreateTeleporter( 789, 1553, -28, 789, 1546, -28, map, false );
				CreateTeleporter( 789, 1545, -28, 779, 1541, -28, map, false );
				CreateTeleporter( 780, 1541, -28, 785, 1554, -28, map, false );
				CreateTeleporter( 785, 1555, -28, 783, 1542, -28, map, false );
				CreateTeleporter( 782, 1542, -28, 785, 1546, -28, map, false );
				CreateTeleporter( 784, 1546, -28, 776, 1548, -28, map, false );
				CreateTeleporter( 777, 1555, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 777, 1553, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 776, 1549, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 777, 1548, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 777, 1547, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 776, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 778, 1541, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 779, 1540, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 779, 1542, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 780, 1554, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 781, 1553, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 782, 1554, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 780, 1550, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 781, 1549, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 781, 1551, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 780, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 781, 1547, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 782, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 783, 1543, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 784, 1542, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 783, 1541, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 782, 1538, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 783, 1537, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 784, 1538, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 786, 1538, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 787, 1539, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 788, 1538, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 788, 1542, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 787, 1541, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 786, 1542, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 785, 1545, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 786, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 785, 1547, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 785, 1549, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 785, 1551, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 786, 1550, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 784, 1554, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 785, 1553, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 786, 1554, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 788, 1556, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 789, 1555, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 790, 1556, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 788, 1552, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 789, 1551, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 790, 1552, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 790, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 788, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 789, 1547, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1545, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1546, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1547, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1549, -28, 798, 1547, -28, map, false );
				CreateTeleporter( 791, 1550, -28, 798, 1547, -28, map, false );

				// Sorcerer`s Dungeon
				CreateTeleporter( 546, 455, -40, 426, 113, -28, map, true );
				CreateTeleporter( 547, 455, -40, 427, 113, -28, map, true );
				CreateTeleporter( 548, 455, -40, 428, 113, -28, map, true );
				CreateTeleporter( 429, 113, -28, 548, 455, -40, map, false );

				CreateTeleporter( 242, 27, -16, 372, 31, -31, map, false ); // stairs - 0x754 
				CreateTeleporter( 242, 26, -16, 372, 30, -31, map, false ); // stairs - 0x754 
				CreateTeleporter( 242, 25, -16, 372, 29, -31, map, false ); // stairs - 0x754 
				CreateTeleporter( 371, 31, -36, 241, 27, -18, map, false ); // stairs - 0x754 
				CreateTeleporter( 371, 30, -36, 241, 26, -18, map, false ); // stairs - 0x754 
				
				DestroyTeleporter( 371, 29, -36, map );	//To remove old erroneous teleporter

				CreateTeleporter( 371, 29, -36, 241, 25, -18, map, false ); // stairs - 0x754

				CreateTeleporter( 272, 141, -16, 555, 427, -1, map, false ); // stairs - 1st 0x753 
				CreateTeleporter( 273, 141, -16, 556, 427, -1, map, false ); // stairs - 1st 0x753 
				CreateTeleporter( 274, 141, -16, 557, 427, -1, map, false ); // stairs - 1st 0x753 
				CreateTeleporter( 555, 426, -6, 272, 140, -21, map, false ); // stairs - 1st 0x753 
				CreateTeleporter( 556, 426, -6, 273, 140, -21, map, false ); // stairs - 1st 0x753 
				CreateTeleporter( 557, 426, -6, 274, 140, -21, map, false ); // stairs - 1st 0x753 

				CreateTeleporter( 265, 130, -31, 284, 72, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 266, 130, -31, 285, 72, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 267, 130, -31, 286, 72, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 268, 130, -31, 287, 72, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 284, 73, -16, 265, 131, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 285, 73, -16, 266, 131, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 286, 73, -16, 267, 131, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 287, 73, -16, 268, 131, -28, map, false ); // stairs - 0x753 

				CreateTeleporter( 284, 67, -30, 131, 128, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 285, 67, -30, 132, 128, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 286, 67, -30, 133, 128, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 287, 67, -30, 134, 128, -21, map, false ); // stairs - 0x753 
				CreateTeleporter( 131, 129, -16, 284, 68, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 132, 129, -16, 285, 68, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 133, 129, -16, 286, 68, -28, map, false ); // stairs - 0x753 
				CreateTeleporter( 134, 129, -16, 287, 68, -28, map, false ); // stairs - 0x753 

				CreateTeleporter( 358, 40, -36, 156, 88, -18, map, false ); // stairs - 0x73A 
				CreateTeleporter( 358, 41, -36, 156, 89, -18, map, false ); // stairs - 0x73A 
				CreateTeleporter( 358, 42, -36, 156, 90, -18, map, false ); // stairs - 0x73A 
				CreateTeleporter( 155, 88, -16, 357, 40, -31, map, false ); // stairs - 0x73A 
				CreateTeleporter( 155, 89, -16, 357, 41, -31, map, false ); // stairs - 0x73A 
				CreateTeleporter( 155, 90, -16, 357, 42, -31, map, false ); // stairs - 0x73A 

				CreateTeleporter( 259, 90, -28, 236, 113, -28, map, true );

				// Ancient Lair

				DestroyTeleporter( 83, 747, -28, map );
				DestroyTeleporter( 84, 747, -28, map );
				DestroyTeleporter( 85, 747, -28, map );
				DestroyTeleporter( 86, 747, -28, map );
				CreateTeleporter( 938, 494, -40, 83, 749, -23, map, true );
				CreateTeleporter( 939, 494, -40, 84, 749, -23, map, true );
				CreateTeleporter( 940, 494, -40, 85, 749, -23, map, true );
				CreateTeleporter( 941, 494, -40, 86, 749, -23, map, true );

				// Lizard Passage

				DestroyTeleporter( 313, 1330, -39, map );
				DestroyTeleporter( 314, 1330, -37, map );
				DestroyTeleporter( 315, 1330, -35, map );
				CreateTeleporter( 313, 1329, -40, 327, 1593, -13, map, true );
				CreateTeleporter( 314, 1329, -38, 328, 1593, -13, map, true );
				CreateTeleporter( 315, 1329, -36, 329, 1593, -13, map, true );
				CreateTeleporter( 330, 1593, -13, 315, 1329, -35, map, false );

				DestroyTeleporter( 225, 1335, -20, map );
				DestroyTeleporter( 226, 1335, -20, map );
				DestroyTeleporter( 227, 1335, -19, map );
				CreateTeleporter( 265, 1587, -28, 225, 1334, -20, map, true );
				CreateTeleporter( 266, 1587, -28, 226, 1334, -20, map, true );
				CreateTeleporter( 267, 1587, -28, 227, 1334, -20, map, true );

				// Central Ilshenar
				/*CreateTeleporter( 1139, 593, -80, 1237, 582, -19, map, true );
				CreateTeleporter( 1140, 593, -80, 1237, 583, -19, map, true );
				CreateTeleporter( 1141, 593, -80, 1237, 584, -19, map, true );
				CreateTeleporter( 1142, 593, -80, 1237, 585, -19, map, true );
				CreateTeleporter( 912, 451, -80, 708, 667, -39, map, true );
				CreateTeleporter( 912, 452, -80, 709, 667, -39, map, true );
				CreateTeleporter( 912, 453, -80, 710, 667, -39, map, true );
				CreateTeleporter( 711, 667, -39, 912, 453, -80, map, false );*/

				// Update: remove old teleporters..
				DestroyTeleporter( 1139, 593, -80, map );
				DestroyTeleporter( 1140, 593, -80, map );
				DestroyTeleporter( 1141, 593, -80, map );
				DestroyTeleporter( 1142, 593, -80, map );
				DestroyTeleporter( 1237, 582, -19, map );
				DestroyTeleporter( 1237, 583, -19, map );
				DestroyTeleporter( 1237, 584, -19, map );
				DestroyTeleporter( 1237, 585, -19, map );

				DestroyTeleporter( 912, 451, -80, map );
				DestroyTeleporter( 912, 452, -80, map );
				DestroyTeleporter( 912, 453, -80, map );
				DestroyTeleporter( 708, 667, -39, map );
				DestroyTeleporter( 709, 667, -39, map );
				DestroyTeleporter( 710, 667, -39, map );
				DestroyTeleporter( 711, 667, -39, map );

				// Update: add new ones...
				CreateTeleporter( 1139, 592, -80, 1238, 583, -19, map, false );
				CreateTeleporter( 1140, 592, -80, 1238, 584, -19, map, false );
				CreateTeleporter( 1141, 592, -80, 1238, 585, -19, map, false );
				CreateTeleporter( 1142, 592, -80, 1238, 585, -19, map, false );
				CreateTeleporter( 1237, 583, -19, 1139, 593, -80, map, false );
				CreateTeleporter( 1237, 584, -19, 1140, 593, -80, map, false );
				CreateTeleporter( 1237, 585, -19, 1141, 593, -80, map, false );

				CreateTeleporter( 709, 667, -39, 912, 451, -80, map, false );
				CreateTeleporter( 710, 667, -39, 912, 452, -80, map, false );
				CreateTeleporter( 711, 667, -39, 912, 453, -80, map, false );

				CreateTeleporter( 911, 451, -80, 709, 668, -39, map, false );
				CreateTeleporter( 911, 452, -80, 710, 668, -39, map, false );
				CreateTeleporter( 911, 453, -80, 711, 668, -38, map, false );

				// Exodus Dungeon
				CreateTeleporter( 827, 777, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 827, 778, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 827, 779, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 828, 777, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 828, 778, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 828, 779, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 829, 777, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 829, 778, -80, 1975, 114, -28, map, false ); 
				CreateTeleporter( 829, 779, -80, 1975, 114, -28, map, false ); 

				CreateTeleporter( 1978, 114, -28, 835, 778, -80, map, false );
				CreateTeleporter( 1978, 115, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1978, 116, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1978, 117, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1979, 114, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1979, 115, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1979, 116, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1979, 117, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1980, 114, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1980, 115, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1980, 116, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1980, 117, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1981, 114, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1981, 115, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1981, 116, -28, 835, 778, -80, map, false ); 
				CreateTeleporter( 1981, 117, -28, 835, 778, -80, map, false );
			}

			public void CreateTeleportersMap3( Map map )
			{
				// CreateTeleporter( 408, 254, 2, 428, 319, 2, map, false ); // for doom quest; use blockers to avoid players teleporting into the ship! 
				// CreateTeleporter( 428, 321, 2, 422, 328, -1, map, false ); // for doom quest; use blockers to avoid players teleporting into the ship!

				// Doom Dungeon
				CreateTeleporter( 2317, 1269, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2317, 1268, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2317, 1267, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2317, 1266, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2316, 1269, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2315, 1269, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2315, 1268, -110, 381, 132, 33, map, false );
				CreateTeleporter( 2315, 1267, -109, 381, 132, 33, map, false );
				CreateTeleporter( 2316, 1267, -110, 381, 132, 33, map, false );
				CreateTeleporter( 496, 49, 6, 2350, 1270, -85, map, false );
				DestroyTeleporter( 433, 326, 4, map );
				DestroyTeleporter( 365, 15, -1, map );
			}


			public void CreateTeleportersTrammel( Map map )
			{
				// Haven
			//	CreateTeleporter( 3632, 2566, 0, 3632, 2566, 20, map, true );
			}

			public void CreateTeleportersFelucca( Map map )
			{
				// Star room
			//	CreateTeleporter( 5140, 1773, 0, 5171, 1586, 0, map, false );
			}

			public int CreateTeleporters()
			{
				CreateTeleportersMap( Map.Felucca );
				CreateTeleportersMap( Map.Trammel );
				CreateTeleportersTrammel( Map.Trammel );
				CreateTeleportersFelucca( Map.Felucca );
				CreateTeleportersMap2( Map.Ilshenar );
				CreateTeleportersMap3( Map.Malas );
				return m_Count;
			}
		}
	}
}

